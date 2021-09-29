/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
Измеритель длительности паузы периодической импульсной последовательности
*****************************************************/
#include <mega16.h>

// Declare your global variables here

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
        TCCR0=0x00;     //Останов TCNT0
        PORTA=TCNT0;    //вывод TCNT0 в порт A
        TCNT0=0;        //сброс TCNT0 для подгот. к след. измерению 
        MCUCR=0x02;     //след. прерывание INT0 - по срезу
        };
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
PORTA=0xFF;             //Вывод на индикацию 0xFF в случае переполнения
TCCR0=0x00;             //Останов TCNT0
TCNT0=0;                //сброс TCNT0 для подгот. к след. измерению 
MCUCR=0x02;             //след. прерывание INT0 - по срезу
}


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;
DDRA=0xFF;                  //порт A - на вывод данных

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

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
TIMSK=0x01;                 //разрешение прерывания по переполнению

// Global enable interrupts
#asm("sei")

while (1);
}
