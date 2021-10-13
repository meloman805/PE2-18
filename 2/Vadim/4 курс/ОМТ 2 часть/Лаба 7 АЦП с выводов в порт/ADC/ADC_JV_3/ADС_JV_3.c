/*****************************************************
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
/*����� ������ ��� �� �������������� - �� ���������� INT0, � ���������� ������ � ��� -
�� ���������� ���������� ������ ���, ����� ��������� INT0 � ������ ��� ���������� �� ����,
��������� ��� ���������� �� �������������� ��� ��������� ����� INT0 � �������� GIFR*/
#include <mega16.h>
#include <delay.h>
#define ADC_VREF_TYPE 0x00  //����������� ������ �������� ��� ��� ���

// ADC interrupt service routine
interrupt [ADC_INT] void adc_isr(void)
{
// Read the AD conversion result
PORTB=ADCL;
PORTC=ADCH;
GIFR|=1<<INTF0;				//����� ����� ���������� INT0 (������� 1!)
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Port B initialization
PORTB=0x00;                 //PORTB - �� ����� ������
DDRB=0xFF;                  //��� ������ �������� ����� ����������

// Port C initialization
PORTC=0x00;                 //4 ��. ������� PORTC - �� ����� ������
DDRC=0x0F;                  //��� ������ �������� ����� ����������

// External Interrupt(s) initialization
// INT0: Off
// INT0 Mode: Falling Edge  //������� ���������� INT0 ����� ���������
// INT1: Off                //������ ��� ���� ��������������� � GIFR
// INT2: Off
//GICR|=0x40;
MCUCR=1<<ISC01;	            //��������� ����� �������� ������. INT0 - �� �����,
MCUCSR=0x00;                //���� ��������� ��� ����� �������������� A��
//GIFR=0x40;

// ADC initialization
// ADC Clock frequency: 250,000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: External IRQ0
ADMUX=0x0B|(ADC_VREF_TYPE & 0xFF);/*��������� ���������� ������ ��� � ���:
���������������� ����� ADC1-ADC0 � ����. �����. �������� 200 � ������� ���, */

ADCSRA=0xAD;        //������� ������. 250 ���, ���������� ����������
                    //�� ���������� ��������������� ������
SFIOR&=0x1F;
SFIOR|=0x40;        //������ �������������� - �� ��������� ����� INT0 � GIFR

// Global enable interrupts
#asm("sei")                         //���������� ����������
while (1);
}
