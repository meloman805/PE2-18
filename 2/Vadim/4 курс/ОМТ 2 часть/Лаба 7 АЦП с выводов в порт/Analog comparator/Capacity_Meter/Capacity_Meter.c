/*Программа измерения величины электрической емкости  с использованием
времяимпульсного преобразования на базе аналогового компаратора*/
#include <mega16.h>
void main(void)
{
// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;
DDRA=0xFF;          //выходы для вывода младшего байта емкости

// Port B initialization
PORTB=0x00;
DDRB=0x01;          //выход для заряда конденсатора

// Port C initialization
PORTC=0x00;
DDRC=0xFF;          //выходы для вывода старшего байте емкости

// Port D initialization
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: On
// Input Capture on Rising Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: On
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0xC0;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=1<<INT1;
MCUCR=1<<ISC11 | 1<<ISC10;
MCUCSR=0x00;
GIFR=1<<INTF1;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<TICIE1;

// Analog Comparator initialization
// Analog Comparator: Off
ACSR=1<<ACD;        //В исходном состоянии AC выключен, включается
SFIOR=0x00;         //и подключается к схеме захвата при запуске измерения

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      };
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
TCNT1H=0x00;        //Обнулить TC1 для подготовки к измерению
TCNT1L=0x00;
PORTB=PORTB|0x1;    /*организация заряда исследуемой емкости напряжением
                    с выхода разряда 0  PORTB*/
TCCR1B=0xC2;        //запустить СТ1 на счет с коэффициентом деления 8 (f=1МГц)
                    //системная тактовая частота 8 МГц
ACSR=1<<ACIC;       //Включить аналоговый компаратор и подкл. его к схеме захвата
}

// Timer1 input capture interrupt service routine
interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
PORTB=PORTB&~(1<<0);    //разрядить емкость
PORTA = ICR1L;          //вывести результат измерения на PORTA и  PORTC
PORTC = ICR1H;
ACSR=1<<ACD;            //Отключить аналоговый компаратор во избежании
                        //генерации повторного прерывания по захвату в конце разряда C1
}

