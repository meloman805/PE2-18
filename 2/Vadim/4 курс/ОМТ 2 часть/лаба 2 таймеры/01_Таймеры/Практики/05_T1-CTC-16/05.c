/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
*****************************************************/

#include <mega16.h>
// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{			            //TCNT1 ���. � 0 ��� ���������� (��� ����. ����������)
// Place your code here	//�.�. ����� ������������ ����� 5-��������� ��������
PORTC=(PINC^0b00000001);	//�������� ��������� LED �� ���������������
}               

void main(void)
{
DDRC=0x01;     	//������ 0 ����� � - �� �����
PORTC=0x01;	    //�������� ������ LED

DDRD=0x20;     	//������ 5 ����� D - �� �����
PORTD=0x00;     //��� ����� ����� ��������� ������ A

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 7,813 kHz
// Mode: CTC top=OCR1A
// OC1A output: Toggle
// Compare A Match Interrupt: On
TCCR1A=0x40;
TCCR1B=0x0D;
OCR1AH=0x98;        //������ � ������� ��������� ������ �
OCR1AL=0x96;        //������������ ������ ����� ��� ����. 5� ��������� 
                    //����� ������������ �� ���������� A

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x10;         //���������� ���������� �� ���������� A

// Global enable interrupts
#asm("sei")
while (1);
}
