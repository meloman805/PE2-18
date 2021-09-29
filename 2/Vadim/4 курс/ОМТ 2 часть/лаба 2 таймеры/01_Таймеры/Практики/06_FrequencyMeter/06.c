/*******************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
*******************************************************/
#include <mega16.h>

// Declare your global variables here

// Timer1 overflow interrupt service routine - ���������� ������������ T1
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Place your code here
//������� ������� TCNT1
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=255;
TCNT1L=255; //������ � �1 ����. ����� ��� ��������� ������������ �� ����������� ������. T2
}

// Timer2 output compare interrupt service routine
interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
// Place your code here
//������� ������� TCNT1
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
PORTA=TCNT1L;   //��������� ���������� ������� � �������� 16-� ���� (HEX 4-�), 
PORTD=TCNT1H;   //� ��� ����� � ������������ 0xFFFF=0b1111111111111111
//������ ������� TCNT1 �� ���� ��������� � �������� ����� � ���� ��� ������������ ���������
//� ������� ���������� ���������� ���������
TCNT1H=0; TCNT1L=0;
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (1<<CS11) | (1<<CS10);
}

void main(void)
{
// Input/Output Ports initialization
// Port A initialization - �� ����� �������� ����� ��. ���� �������
DDRA=(1<<DDA7)|(1<<DDA6)|(1<<DDA5)|(1<<DDA4)|(1<<DDA3)|(1<<DDA2)|(1<<DDA1)|(1<<DDA0);
PORTA=(0<<PORTA7)|(0<<PORTA6)|(0<<PORTA5)|(0<<PORTA4)|(0<<PORTA3)|(0<<PORTA2)|(0<<PORTA1)|(0<<PORTA0);

// Port D initialization - �� ����� �������� ����� ��. ���� �������
DDRD=(1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(1<<DDD4)|(1<<DDD3)|(1<<DDD2)|(1<<DDD1)|(1<<DDD0);
PORTD=(0<<PORTD7)|(0<<PORTD6)|(0<<PORTD5)|(0<<PORTD4)|(0<<PORTD3)|(0<<PORTD2)|(0<<PORTD1)|(0<<PORTD0);

// Timer/Counter 1 initialization
// Clock source: T1 pin Rising Edge -  ����� Normal ����� ��������� � �������� ����� �� T1
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: On - ���������� ���������� �� ������������
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: TOSC1 pin - �������� �������� ��������� ������� ��������� ��������� f=32768��
// Clock value: PCK2/256 - ����������� ������� ������������ 256, ������� ������������ T2 ft2=32768/256=128��
// Mode: CTC top=OCR2A   - ����� ����� ��� ����������, ������ ����� � OCR2
// OC2 output: Disconnected
ASSR=1<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (1<<CTC2) | (1<<CS22) | (1<<CS21) | (0<<CS20);
TCNT2=0;
OCR2=127; //������������� ���������� �� ���������� �2 ����� �������� ������ (1/ft2)*(OCR2+1)=1 ���

// Timer(s)/Counter(s) Interrupt(s) initialization - ���������� ���������� �� ���������� T2 � ��������. T1
TIMSK=(1<<OCIE2)|(0<<TOIE2)|(0<<TICIE1)|(0<<OCIE1A)|(0<<OCIE1B)|(1<<TOIE1)|(0<<OCIE0)|(0<<TOIE0);

// Global enable interrupts - ���������� ���������� ����������
#asm("sei")

while (1);  //������ ����������� ���� - ������� ���������

}
