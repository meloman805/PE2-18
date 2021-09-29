#include <mega16.h>

// External Interrupt 1 service routine, ���������� �������� ���������� INT1
interrupt [EXT_INT1] void ext_int1_isr(void)
{
TCNT0=0x00;         //������ ��0 � ����
TCCR0=0x07;         //� ������ ����� ��������� � �������� ����� PB0/T0
TCCR1B=0x05;        //������ ��1 - ������ ������������ ���
}

// Timer1 output compare A interrupt service routine, ���������� ���������� �� ���������� A
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
TCCR0=0x00;         //������� TC0
TCCR1B=0x00;        //������� TC1
TCNT1H=0x00;        //��������� �������� �������� TC1
TCNT1L=0x00;        //��� ����, ����� ����������� ��������� ���� ������
PORTA=TCNT0;        //����� � ���� A ������� � ������
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization, ��� ������� ����� A - �� ����� � �������� ���. ����������
PORTA=0x00;
DDRA=0xFF;

// Port B initialization
PORTB=0x00;
DDRB=0x00;

// Port C initialization
PORTC=0x00;
DDRC=0x00;

// Port D initialization
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;         //� �������� ��������� TC0 ���������� � �������
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;        //� �������� ��������� TC1 ���������� � �������
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x1E;        //��������� � ������� ��������� A ��������
OCR1AL=0x85;        //��� ������������ T��=1��� (7813)
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=1<<INT1;              //���������� �������� ���������� INT1
MCUCR=1<<ISC11 | 1<<ISC10;  //������ - �� ��������� ������
MCUCSR=0x00;
GIFR=1<<INTF1;				//����� ����� ����������

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<OCIE1A;			//���������� ���������� �� ���������� A TC1

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// Global enable interrupts
#asm("sei")         //���������� ����������

while (1)           //����������� ����
      {
      };
}
