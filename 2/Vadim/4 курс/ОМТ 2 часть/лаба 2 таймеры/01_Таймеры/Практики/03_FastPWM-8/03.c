/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
*****************************************************/
#include <mega16.h>
// Declare your global variables here
void main(void)
{
// Declare your local variables here
PORTB=0x00;
DDRB=0x08;          //PB3 (OC0) -  � ������ ������

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Fast PWM top=0xFF
// OC0 output: Non-Inverted PWM
TCCR0=0x69;
TCNT0=0x00;
OCR0=0x00;

while (1)
      {
      // Place your code here   //����� � OCR0 ��� �� ������ ����� A, 
      OCR0=PINA;                //������� ��� ����� ����������� ����������   
      }                         //�������������� ���-������� � �������� 8���/256              
}
