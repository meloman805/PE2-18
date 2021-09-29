/*��������� ������������� ������� �� ������� �����������. ����� ��� �����������
��������� �������� ������������ ���������� �� ���������� � ������� TC1, �����������
� ������ ���. ������� � ����� ����� ����������� � ��������� ����������� ���������� 
� ����������� ����� ����������*/
/*****************************************************
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
#include <mega16.h>
#include <delay.h>

// Declare your global variables here
char A[13] = {0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x40,0x00,0x00,0x00};
char B[13] = {0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x80,0x00,0x00};
char C[13] = {0x00,0x00,0x00,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x80,0x00};
char D[13] = {0x00,0x00,0x00,0x00,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x40};
char i=0;

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
// Place your code here
i++;                //��������� ��������� �� ��������� ������� ���� 4-� ��������
                    //������� TC1 �������� �� ����, ��������� �� ��������� ��� (����� CTC)
if (i==13)	        //���� ���� ������ �����������,
    {
    PORTA=0x00;     //����� ��� ����������
    PORTB=0x00;		//� ����� �������� �������� (0,25 ���)
    PORTC=0x00; 	//�������� ��� ������
    PORTD=0x00;
    i=-1;
    }
else                //���� �� ���� ������ ����������,
    {               //����������� ��������� �����������
    PORTA|=A[i];	//� ��������� ��� | - ���������� ������������� �����,
    PORTB|=B[i];	//�.�. �������� ����������� ����� ��������� ����������
    PORTC|=C[i];	//��� �������� ��� (������� ������������ ������
    PORTD|=D[i];    //��������� �������) - ������� ����� �� ������� �������
    };
}                           

void main(void)
{
// Declare your local variables here
// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;         //POPTA - �� ����� ������
DDRA=0xFF;

// Port B initialization
PORTB=0x00;         //POPTB - �� ����� ������
DDRB=0xFF;

// Port C initialization
PORTC=0x00;
DDRC=0xFF;          //POPTC - �� ����� ������

// Port D initialization
PORTD=0x00;
DDRD=0xFF;          //POPTD - �� ����� ������

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 7,813 kHz
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x0D;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x07;        //��� ����� �� ���� �� ���� ������� ��������
OCR1AL=0xA1;        //����� t=0x7A1/7813=1953/7813=0.25 ��� -
OCR1BH=0x00;        //�������� ������������� ��������� ����� �������
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<OCIE1A;    //���������� ���������� �� ���������� A TC1

// Global enable interrupts
#asm("sei")         //����� ���������� ����������

while (1)			//����������� ���� (������� ���������)
    {				    
    //Place your code here
    }				//����� ������������ ����� (������� ���������)
}                   //����� ������� �������

