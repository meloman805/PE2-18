/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
*****************************************************/
#include <mega16.h>
// Declare your global variables here
unsigned char seconds=0;        //���������� ��� ������� �������
unsigned char minutes=0;        //��������� �����������
unsigned char hours=0;          //����� ��� ���� �������� ���� ��������
unsigned char days=0;           //� �� ����� ���� ���������� � ��������� ��

// Timer2 output compare interrupt service routine
interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
seconds++;
if (seconds==60) 
    {
    minutes++;
    seconds=0;
    if (minutes==60) 
        {
        hours++;
        minutes=0;
        if (hours==24) 
            {
            days++;
            hours=0;
            if (days==32)
                days=0;
            }    
        }    

    };
PORTA=seconds;
PORTB=minutes;
PORTC=hours;
PORTD=days;    
}

void main(void)
{
// Declare your local variables here
PORTA=0x00;
DDRA=0x3F;

PORTB=0x00;
DDRB=0x3F;

PORTC=0x00;
DDRC=0x1F;      //5 ������� ��� �� �����

PORTD=0x00;
DDRD=0x9F;     //OC2=PD.7 - ����� � 5 ������� ��� �� ����� ��� �����. ����

// Timer/Counter 2 initialization
// Clock source: TOSC1 pin
// Clock value: PCK2/256
// Mode: CTC top=OCR2
// OC2 output: Toggle on compare match
ASSR=0x08;
TCCR2=0x1E;         //������� ������������ TCNT2 32768/256=128��
TCNT2=0x00;
OCR2=127;           //����� � OCR2 ������������� ������������� ���������� 
                    //�� ���������� � ������ CTC ������ �������

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x80;         //���������� ���������� �� ���������� TCNT2

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      }
}
