#include <mega16.h>
#include <delay.h>
//Declare your global variables here
//���������� ������� 10 ���������� ���� (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������,
unsigned char BCD_UNPACKED[4]={6,7,8,9};        //����� ������ �������
unsigned char i=0;  //������ ��������� ������� ������������� ���. ����
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{                   //�������� ����� TC0 �� ���� - �� ��� ��������� ��� ���������� � ��������� ���������� (����� CTC)
PORTB=0x00;         //������� �������� ����������, ���������� ��� ������ PROTEUS
PORTC=0x00;         //��� ��������� ���������� �������������
//delay_us(5);
PORTB=0b1000>>i;    //�������� �������� ���� ���������� ����������
PORTC=DIG_DEC[BCD_UNPACKED[i]];     //��� ������� ����� 7-���. ������� ��� ���������� ���������� - � ���� C
i++;                //��������� � ����. ���������� ����� � ������� ������. ����
if (i>3) i=0;       //���� ��������� ��������� ������� �������, �������� ����� ����
}

void main(void)     //�������� �������
{
// Input/Output Ports initialization
PORTB=0x00;
DDRB=0x0F;          //������� PB3...PB0 � �� ����� ������ (����� ������)
PORTC=0x00;
DDRC=0xFF;          //Port C - �� ����� ������ (������ ���������)

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 31,250 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
TCCR0=0x0C;         //������ ������� � �������� Fclk/256=31,25kHz � ������ CTC
TCNT0=0x00;
OCR0=77;            //�������� �������� ��������� ������, ��������������
                    //���� �� ���� �� ���������� � ������� 2.5 ��

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<OCIE0;                         //���������� ���������� �� ���������� TC0
#asm("sei")                             //���������� ���������� ����������
while (1)                               //����������� ���� (������� ���������)
    {
    };        
}
