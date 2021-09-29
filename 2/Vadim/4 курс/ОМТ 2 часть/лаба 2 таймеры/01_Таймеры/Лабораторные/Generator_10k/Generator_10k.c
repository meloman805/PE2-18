/*Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
������������� ��������� ������������� ��������� � ��������
���������� ��������� f  = 10 ���. ��������� ������
�����������-��������������� ��� ������ ����� �������
������. ��� ����������� ��������� ������ ������������
���� ���������� ���������������� INT1
*****************************************************/

#include <mega16.h>
bit i=0;                //����������� ���������� ������� ���������� i=0
// External Interrupt 1 service routine, ���������� �������� ���������� �� ����� IN1
interrupt [EXT_INT1] void ext_int1_isr(void)
{
 if (i==0)
    {                   //���� ��������� ���� �����������, �� ������ ���������
    TCCR0=0x1A;
    i=1;
    }
 else                   //���� ���� ���������, �� ���������� ��
    {
    TCCR0=0x18;
    i=0;
    }
}

void main(void)
{

// Input/Output Ports initialization
// Port B initialization  (������ PortB.3 �� �����)
// Func7=in Func6=In Func5=In Func4=In Func3=Out Func2=In Func1=In Func0=In
PORTB=0x00;
DDRB=0x08;

// Port D initialization (��� ������� PortB �� ����, ��� ����������� �����. ������. ����������)
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: CTC top=OCR0
// OC0 output: Toggle on compare match
TCCR0=0x18;             //����� CTC, ������ CT0 ����������
TCNT0=0x00;             //� TC0 - 0
OCR0=0x31;              //������� ��������� TC0 OCR0=49

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Low level
// INT2: Off
GICR|=1<<INT1;
MCUCR=0x00;             //������ ���������� - ������ ������� �� ����� INT1
MCUCSR=0x00;
GIFR=1<<INTF1;          //����� ����� ���������� (������� ���. �1�!)

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;             //��� ���������� �� ������� ���������


// Global enable interrupts
#asm("sei")

while (1)               //����������� ����
      {
      };
}
