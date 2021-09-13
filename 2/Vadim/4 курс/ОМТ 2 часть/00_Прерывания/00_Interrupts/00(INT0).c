/*******************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 12,000000 MHz
������� ������� ������� (������ �������������� ������) �
������������� ������� �����������, ������������ � ������ 
PORTC.0
*******************************************************/
#include <mega16.h>
#include <delay.h>
// Declare your global variables here
unsigned char counter=0;    //���������� ��� ����� �������
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
//���������� ����������, ������������� counter ��� ����� ������
counter++;
PORTA=counter;  //����� counter � ���� A
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
DDRA=0b11111111;    //PORTA - ��� ���� �� ����� ������
PORTA=0b00000000;

// Port C initialization
DDRC=0b00000001;        //������� ��� PORTC - �� �����
PORTC=0b00000000;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: Off
// INT2: Off
GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (1<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here 
      //������� ��������� ������� ���������� �� ������ 0 ����� C
      PORTC=0b00000001;
      delay_ms(250);
      PORTC=0b00000000;
      delay_ms(250);
      }
}
