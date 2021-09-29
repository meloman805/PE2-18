/************************************************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
Измеритель длительности паузы периодической импульсной последовательности в мкс
Динамическая индикация организована с помощью прерывания от таймера TCNT2
по совпадению в режиме CTC, происходящего через каждые 2.5 мс (длительность 
подсветки одного знакоместа).
Измерение длительности паузы организовано с помощью внешнего прерывания INT0
(по срезу - запускается подсчет импульсов с эталонной частотой 1МГц таймером TCNT0,
по фронту - счет останавливается и содержимое TCNTO преобразуется в двоично-десятичный
4-хразрядный распакованный код длительности паузы в микросекундах, который обработчиком 
прерывания по совпадению TCNT2 выводится на 4-хразрядный семисегментный индикатор).
Фоновая программа - пустой бесконечный цикл, прерываемый обработчиками прерываний.
*************************************************************************************/
#include <mega16.h>
#include <bcd.h>        //подключение библиотеки двоично-десятичных преобразований
// Declare your global variables here
//библиотека графики 10 десятичных цифр и "-" для переполнения (знакогенератор)
//////////////////////////0////1////2////3////4////5////6////7////8////9////-//
flash char DIG_DEC[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
//число мкс в паузе в распакованном BCD (одна цифра в одном байте), ст. байт по младшему адресу
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //в исх. сост. на инд. 0000
unsigned char n_znak;                       //номер подсвечиваемого знакоместа, здесь глобальная
                                            //переменная, доступная обработчикам прерываний
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
if (MCUCR==0x02) 
        {
        TCCR0=0x02;     //Запуск TCNT0 на счет от 0 в NORMAL c f=1МГЦ
        MCUCR=0x03;     //следующее прерывание (конец паузы) - по фронту
        }
else  
        {
        unsigned char sot=0, pause;
        TCCR0=0x00;     //Останов TCNT0
        PORTA=TCNT0;    //вывод TCNT0 в порт A
        pause=TCNT0;    //и в переменную pause
        TCNT0=0;        //сброс TCNT0 для подгот. к след. измерению 
        MCUCR=0x02;     //след. прерывание INT0 - по срезу
        while (pause>=100) 
            {
            pause-=100, sot++;
            };          //Здесь в sot - количество сотен микросекунд (<=99), в pause - кол-во микросекунд (<=99)
        sot=bin2bcd(sot);       //библиотечная функция преобразования в упакованный BCD, здесь тысячи и сотни
        pause=bin2bcd(pause);   //здесь десятки и единицы
        //получение распакованного BCD кода цифр из упакованного
        BCD_UNPACKED[0]=sot>>4, BCD_UNPACKED[1]=sot&0x0F, BCD_UNPACKED[2]=pause>>4,BCD_UNPACKED[3]=pause&0x0F; 
        };
}

// Timer 0 overflow interrupt service routine - индикация "----" в случае переполнения
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
unsigned char i;
PORTA=0xFF;             //Вывод на индикацию в порт A 0xFF в случае переполнения
for (i=0;i<4;i++) 
    {
    BCD_UNPACKED[i]=10; //код изображения "-" на 7SEG, 
    };                  // в случае переполнения на 7SEG индицируется "----"
TCCR0=0x00;             //Останов TCNT0
TCNT0=0;                //сброс TCNT0 для подгот. к след. измерению 
MCUCR=0x02;             //след. прерывание INT0 - по срезу
}

// Timer2 output compare interrupt service routine - смена индицируемых семисегментных знакомест при динамической индикации
interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
// Смена знакоместа при динамической индикации
PORTB=0xFF;                         //Кратковременное гашение текущего знакоместа (для модели PROTEUS)
PORTB=~(0b00001000>>n_znak);        //Включаем катод очередного знакоместа (низким уровнем)
PORTC=DIG_DEC[BCD_UNPACKED[n_znak]];//Код знака 7-сег. дисплея для очередного знакоместа
n_znak++;                           //переходим к след. десятичной цифре и след. знакоместу
if (n_znak>3) n_znak=0;             //Если прошли все знакоместа, начинаем цикл дин. инд. сначала
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;
DDRA=0xFF;                  //порт A - на вывод данных
PORTB=0xFF;
DDRB=0x0F;                  //порт B (младшие 4 бита) - на вывод данных
PORTC=0x00;
DDRC=0xFF;                  //порт C - на вывод данных

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 31,250 kHz
// Mode: CTC top=OCR2
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x0E;
TCNT2=0x00;
OCR2=77;                   //При данном значении OCR2 интервал между прерываниями по совпадению 
                           //в режиме CTC - (77+1)/31250=2.5 мс
// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=0x40;
MCUCR=0x02;
MCUCSR=0x00;
GIFR=0x40;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x81;                //разрешение прерываний: по переполнению TCNT0 и по совпадению TCNT2

// Global enable interrupts
#asm("sei")
while (1);
}
