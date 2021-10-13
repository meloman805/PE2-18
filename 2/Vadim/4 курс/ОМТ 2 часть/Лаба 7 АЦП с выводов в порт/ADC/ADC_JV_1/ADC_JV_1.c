/*****************************************************
Project : ADC
Version :
Date    : 15.10.2014
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
/*����� ������ ��� �� �������������� - �� ���������� INT0, � ���������� ������ � ��� -
�� ������ ���������� (��������), ��� ��� �������� ������ ����������� INT0*/
#include <mega16.h>
#include <delay.h>

#define ADC_VREF_TYPE 0x00 //��������� ��� ������ �������� �������� ���������

/* Read the AD conversion result: ������� ����������
���������� �������-��������� �������������� */
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);//��������� ���������� �������� ��������� � ������ ���
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
//ADCSRA|=1<<ADSC;	//������ ��� �� ������. � ����� �� ����� (��� �������)
// Wait for the AD conversion to complete
while ((ADCSRA & 1<<ADIF)==0);          /*������� ��������� ��������������
                                        (���� �� ����������� ���� ���������� ��� ADIF)*/
ADCSRA|=1<<ADIF;                        //���������� ���� ���������� � ��������� ������
return ADCW; //������������  �������� - ���������� �������� ������ ���
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{               //��� �� ����� ���������� ��� ���������� �� ��������������
read_adc(0);    /*���������� ���������� �������������� �� ����
                ��������� � ������� �������������� �������, ����������� �� ���� AIN0*/
PORTB=ADCL;
PORTC=ADCH;
}

void main(void)
{
// Port B initialization
PORTB=0x00;     //���� B - �� ����� ������
DDRB=0xff;      //��� ������ �������� ����� ��������������� ��� ������

// Port C initialization
PORTC=0x00;     //���� � - �� ����� ������
DDRC=0xff;      //��� ������ �������� ����� ��������������� ��� ������

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=1<<INT0;  //���������� ���������� INT0
MCUCR=1<<ISC01; //������ ���������� - �� ������� ������ INT0
MCUCSR=0x00;
GIFR=1<<INTF0;

// ADC initialization
// ADC Clock frequency: 250,000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: External IRQ0
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0xA5;    //������� 250 ���, ������ � �����. � ���. �������� 7-5 SFIOR
SFIOR&=0x1F;
SFIOR|=0x40;    //������ �� �������� ���������� INT0

// Global enable interrupts
#asm("sei")

while (1)       //����������� ����, ����� �� ��������  ����������
      {         //�� ����������� INT0
      // Place your code here
      };
}
