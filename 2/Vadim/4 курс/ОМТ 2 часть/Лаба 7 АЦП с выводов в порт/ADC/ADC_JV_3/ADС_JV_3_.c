/*****************************************************
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
#define ADC_VREF_TYPE 0x00

/*Read the AD conversion result - ������� ����������
���������� �������-��������� �������������� */
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);//��������� ���������� �������� ��������� � ������ ���
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);             /*������� ��������� ��������������
                                        (���� �� ����������� ���� ���������� ���)*/
ADCSRA|=0x10;                           //���������� ���� ���������� � ��������� ������
return ADCW;                //������������  �������� - ���������� �������� ������ ���
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{                       //��� �� ����� ���������� ��� ���������� �� ��������������
// Place your code here
read_adc(0x0B);         //��������� ����������������� �������
PORTB=ADCL;             //ADC1-ADC0 � ����� �������� 200x
PORTC=ADCH;             //����� ���������� � ����� C, B
}


// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Port B initialization
PORTB=0x00;             //���� B - �� ����� ������
DDRB=0xFF;              //��� ������ �������� ����� ��������������� ��� ������

// Port C initialization
PORTC=0x00;             //4 ��. ���� ����� � - �� ����� ������
DDRC=0x0F;              //��� ������ �������� ����� ��������������� ��� ������


// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=0x40;             //���������� ���������� INT0
MCUCR=0x02;             //������ ���������� - �� ������� ������ INT0
MCUCSR=0x00;
GIFR=0x40;

// ADC initialization
// ADC Clock frequency: 250,000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: External IRQ0
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0xA5;            //������� 250 ���, ������ � �����. � ���. �������� 7-5 SFIOR
SFIOR&=0x1F;
SFIOR|=0x40;            //������ �� �������� ���������� INT0

// Global enable interrupts
#asm("sei")

while (1);

}
