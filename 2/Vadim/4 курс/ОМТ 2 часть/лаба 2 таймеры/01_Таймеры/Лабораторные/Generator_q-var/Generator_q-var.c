//��������� �������� ������� 8 MHz
#include <mega16.h>

char a=1;                               //���������� ���������� ��������� �����

//Timer2 overflow interrupt service routine, ���������� ���������� �� ������������ TC2
interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
// Place your code here
switch (a)
    {
    case 1: OCR2=63; break;         //���� a=1, �� OCR2=64
    case 2: OCR2=31; break;         //���� a=2, �� OCR2=32
    case 3: OCR2=15; break;         //���� �=3, �� OCR2=16
    case 4: OCR2=127; a=0; break;   //���� �=4, �� OCR2=128; a=0;
    default:a=0;                    //���� �� ����������� �� ���� �� �������, a = 0
    }
a++;
}

// Declare your global variables here

void main(void)                         //������� �������
{
// Declare your local variables here

// Input/Output Ports initialization

//Port A � ������ �����
PORTA=0x00;
DDRA=0x00;

//Port B � ������ �����
PORTB=0x00;
DDRB=0x00;

//Port � � ������ �����
PORTC=0x00;
DDRC=0x00;

// PD.7 (����� ����� ��������� OC2) � ������ ������
PORTD=0x00;
DDRD=0x80;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 125,000 kHz
// Mode: Fast PWM top=FFh
// OC2 output: Non-Inverted PWM
ASSR=0x00;              //����������� ����� ��������
TCCR2=0x6C;             //FastPWM, ����������������� ���, K=64
TCNT2=0x00;
OCR2=127;               //��� ���������� q=2 � 1-�� ������� ���-�������

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<TOIE2;         //���������� ���������� �� ������������ �������� �������� TC2

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// Global enable interrupts
#asm("sei")             //���������� ����������

while (1)               //����������� ����
      {
      };
}
