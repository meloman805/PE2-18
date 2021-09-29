/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
���������� ������������ ����� ������������� ���������� ������������������
*****************************************************/
#include <mega16.h>

// Declare your global variables here

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
if (MCUCR==0x02) 
        {
        TCCR0=0x02;     //������ TCNT0 �� ���� �� 0 � NORMAL c f=1���
        MCUCR=0x03;     //��������� ���������� (����� �����) - �� ������
        }
else  
        {
        TCCR0=0x00;     //������� TCNT0
        PORTA=TCNT0;    //����� TCNT0 � ���� A
        TCNT0=0;        //����� TCNT0 ��� ������. � ����. ��������� 
        MCUCR=0x02;     //����. ���������� INT0 - �� �����
        };
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
PORTA=0xFF;             //����� �� ��������� 0xFF � ������ ������������
TCCR0=0x00;             //������� TCNT0
TCNT0=0;                //����� TCNT0 ��� ������. � ����. ��������� 
MCUCR=0x02;             //����. ���������� INT0 - �� �����
}


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;
DDRA=0xFF;                  //���� A - �� ����� ������

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
TIMSK=0x01;                 //���������� ���������� �� ������������

// Global enable interrupts
#asm("sei")

while (1);
}
