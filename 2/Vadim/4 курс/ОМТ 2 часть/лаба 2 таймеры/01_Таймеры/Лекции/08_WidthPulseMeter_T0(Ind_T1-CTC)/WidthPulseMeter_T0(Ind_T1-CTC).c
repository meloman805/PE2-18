#include <mega16.h>
#include <delay.h>
#include <bcd.h>            //библиотечная функция преобразования дв. числа (0...99) в упакованное BCD
// Declare your global variables here
//библиотека графики 10 десятичных цифр (знакогенератор)
flash unsigned char  DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//число в распакованном BCD (одна цифра в одном байте), ст. байт по младшему адресу
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //в исходном состоянии на индикаторе 0000
/*Здесь znakomesto и i - глобальные, посккольку к ним должен быть доступ из обработчика совпадения T1*/
unsigned char i=0;                           //индекс элементов массива расп. дес. цифр

//////////External Interrupt 1 service routine, обработчик внешнего прерывания на входе INT1//////////
interrupt [EXT_INT1] void ext_int1_isr(void)
{
if (MCUCR==0x0C)    {
                    MCUCR=0x08;     //изменить тип прерывания - по срезу
                    TCCR0=0x02;     //если прерывание было по фронту - запустить T0
                    }
else                {
                    //двоичное время и его десятичные разряды - однобайтные целые без знака
                    unsigned char sot=0, bin_time;
                    TCCR0=0x00;     //если прерывание по срезу - остановить T0
                    bin_time=TCNT0; //время в двоичном коде запомнить для послед. преобразований
                    PORTA=TCNT0;    //вывести время в мкс в дв. коде в PORTA
                    TCNT0=0x00;     //обнулить TCNT0 для последующих измерений
                    MCUCR=0x0C;     //изменить тип прерывания - по фронту, начать преобразование в распак. BCD


                    sot=0;
                    while (bin_time>=100)   //Начинаем считать сотни
                        {
                        bin_time-=100; sot++;
                        };                          //Здесь в bin_time остается число единиц (0...99)
                    sot=bin2bcd(sot);               //Находим упакованный BCD-код числа сотен (0...99)
                    bin_time=bin2bcd(bin_time);     //Находим упакованный BCD-код числа единиц (0...99)
                    BCD_UNPACKED[0]=sot>>4;         //Получаем распакованный BCD числа тысяч (0...9)
                    BCD_UNPACKED[1]=sot&0x0F;       //Получаем распакованный BCD числа сотен (0...9)
                    BCD_UNPACKED[2]=bin_time>>4;    //Получаем распакованный BCD числа десятков (0...9)
                    BCD_UNPACKED[3]=bin_time&0x0F;  //Получаем распакованный BCD числа единиц (0...9)
                    };
}
////////// Timer1 output compare A interrupt service routine, обр. прер. по совп. A TC1//////////
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{                   //Обнулять здесь TC1 не надо - он сам сбросился при совпадении и генерации прерывания (режим CTC)
PORTB=0x00;         //Гашение текущего знакоместа, необходимо для модели PROTEUS
PORTC=0x00;         //Для реального индикатора необязательно
//delay_us(50);
PORTB=0b1000>>i;                    //Включаем катодный ключ очередного знакоместа
PORTC=DIG_DEC[BCD_UNPACKED[i]];     //Код знака 7-сег. дисплея для очередного знакоместа
i++;                //переходим к след. десятичной цифре и след. знакоместу
if (i>3) i=0;       //Если прошли все знакоместа, начинаем цикл дин. инд. сначала
}

////////////////////Главная функция////////////////////
void main(void)
{
// Declare your local variables here

PORTA=0x00;
DDRA=0xFF;                          //порт A - на вывод, вывод в него нулей

PORTB=0x00;
DDRB=0x0F;                          //4 мл. разряда PORTB - на вывод

PORTC=0x00;
DDRC=0xFF;                          //порт С - на вывод, вывод в него нулей

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;                         //Таймер T0 остановлен с нулевым значением
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x09;        //запуск таймера с сист. частотой в реж. CTC
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x4E;        //загрузка регистра сравнения числом, обеспечивающем
OCR1AL=0x20;        //счет от нуля до совпадения в течение 2,5 мс (частота развертки 100 Гц)
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x10;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=0x80;                         //Разрешение внешнего прерывания INT1
MCUCR=0x0C;                         //Запрос прер. - передний фронт на входе INT1
MCUCSR=0x00;
GIFR=0x80;

// Global enable interrupts
#asm("sei")

while (1)                               //бесконечный цикл (фоновая программа)
      {                                 //Смена индикации знакомест происходит в обработчике прерывания по совпадению A timer1_compa_isr
      // Place your code here
      };
}
