#include <mega16.h>
#include <delay.h>
//Declare your global variables here
//библиотека графики 10 десятичных цифр (знакогенератор)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//число в распакованном BCD (одна цифра в одном байте), ст. байт по младшему адресу,
unsigned char BCD_UNPACKED[4]={6,7,8,9};        //здесь задано заранее
unsigned char i=0;  //индекс элементов массива распакованных дес. цифр
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{                   //Обнулять здесь TC0 не надо - он сам сбросился при совпадении и генерации прерывания (режим CTC)
PORTB=0x00;         //Гашение текущего знакоместа, необходимо для модели PROTEUS
PORTC=0x00;         //Для реального индикатора необязательно
//delay_us(5);
PORTB=0b1000>>i;    //Включаем катодный ключ очередного знакоместа
PORTC=DIG_DEC[BCD_UNPACKED[i]];     //Код графики знака 7-сег. дисплея для очередного знакоместа - в порт C
i++;                //переходим к след. десятичной цифре в массиве распак. цифр
if (i>3) i=0;       //Если обработан последний элемент массива, начинаем новый цикл
}

void main(void)     //Основная функция
{
// Input/Output Ports initialization
PORTB=0x00;
DDRB=0x0F;          //Разряды PB3...PB0 – на вывод данных (общие катоды)
PORTC=0x00;
DDRC=0xFF;          //Port C - на вывод данных (выводы сегментов)

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 31,250 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
TCCR0=0x0C;         //запуск таймера с частотой Fclk/256=31,25kHz в режиме CTC
TCNT0=0x00;
OCR0=77;            //загрузка регистра сравнения числом, обеспечивающем
                    //счет от нуля до совпадения в течение 2.5 мс

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<OCIE0;                         //разрешение прерывания по совпадению TC0
#asm("sei")                             //Глобальное разрешение прерываний
while (1)                               //Бесконечный цикл (фоновая программа)
    {
    };        
}
