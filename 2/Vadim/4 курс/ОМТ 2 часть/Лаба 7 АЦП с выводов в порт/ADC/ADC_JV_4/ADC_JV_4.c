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
#define ADC_VREF_TYPE 0x00          //����������� ���������� ���

// ADC interrupt service routine - ���������� ������. �� ������. ������ ���
interrupt [ADC_INT] void adc_isr(void)
{
// Place your code here
PORTB=ADCL;                         //����� ���������������� ��������
PORTC=ADCH;                         //�� ��������� (� �������� ����)
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Port B initialization
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
PORTC=0x00;
DDRC=0x0F;

// ADC initialization
// ADC Clock frequency: 250,000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: Free Running
ADMUX=ADC_VREF_TYPE & 0xff;         //��������� ���������� ���,
ADMUX|=0x09;                        //������ (ADC1-ADC0) � Ku=10
ADCSRA=0xAD;                        //���������� ���������� �� ���, ������� 250 ���
                                    //����� ������� � ����� ADTS2...0 SFIOR
SFIOR&=0x1F;                        //����� ������������ ��������������
ADCSRA|=1<<ADSC;                    //������ ������ �������������� ���

// Global enable interrupts
#asm("sei")
while (1)                           //����������� ���� ������� ���������
      {
      // Place your code here
      }
}
