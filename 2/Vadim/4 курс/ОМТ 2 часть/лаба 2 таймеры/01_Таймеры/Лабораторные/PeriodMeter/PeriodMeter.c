//��������� �������� ������� 8 MHz
#include <mega16.h>
bit b=0;                    //���������� ���������� ������� ����������
// Timer1 input capture interrupt service routine, ���������� ���������� �� �������
interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
if (b==0)
        {
        TCCR1B=0xC2;        //������ T1 �� ���� � �������� �������� � �������� �� 8
        b=1;                //��������� ������� �� ����������� ����������
        }
else
        {
        TCCR1B=0xC0;        //������� TC1
        PORTA=ICR1L;        //����� �������� ������� ICR1
        PORTB=ICR1H;        //� ����� A � B
        TCNT1H=0x00;        //��������� ������� TC1 ��� ����������� ���������
        TCNT1L=0x00;
        b=0;                //��������� ������� �� ����������� ����������
        };
}

void main(void)             //������� �������
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization, PORTA - �� ����� � ���������� �������� ������
PORTA=0x00;
DDRA=0xFF;

// Port B initialization, PORTB - �� ����� � ���������� �������� ������
PORTB=0x00;
DDRB=0xFF;

// Port C initialization, PORTC - �� ���� ��� ������������� ����������
PORTC=0x00;
DDRC=0x00;

// Port D initialization, PORTD - �� ���� ��� ������������� ����������
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
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

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<TICIE1;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=1<<ACD;
SFIOR=0x00;

// Global enable interrupts
#asm("sei")

while (1)       //����������� ����
      {
      };
}
