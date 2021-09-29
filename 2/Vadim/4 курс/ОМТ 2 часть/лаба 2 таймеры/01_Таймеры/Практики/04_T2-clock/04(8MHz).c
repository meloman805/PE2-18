/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
*****************************************************/
#include <mega16.h>
// Declare your global variables here
unsigned char seconds=0;        //���������� ��� ������� �������
unsigned char minutes=0;        //��������� �����������
unsigned char hours=0;          //����� ��� ���� �������� ���� ��������
                                //� �� ����� ���� ���������� � ��������� ��
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
            hours=0;
        }

    }
PORTA=seconds;
PORTB=minutes;
PORTC=hours;    
}

void main(void)
{
// Declare your local variables here
PORTA=0x00;
DDRA=0x3F;

PORTB=0x00;
DDRB=0x3F;

PORTC=0x00;
DDRC=0x3F;

PORTD=0x00;
DDRD=0x80;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 7,813 kHz
// Mode: CTC top=OCR2
// OC2 output: Toggle on compare match
ASSR=0x00;
TCCR2=0x1F;
TCNT2=0x00;
OCR2=255;           //����� � OCR2 ������������� ������������� ���������� 
                    //�� ������������ � ������ CTC ������ 0,033 ���

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x80;         //���������� ���������� �� ���������� TCNT2

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      }
}
