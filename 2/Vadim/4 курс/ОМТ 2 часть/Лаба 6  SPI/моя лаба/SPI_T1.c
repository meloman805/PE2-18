/****************************************************
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
//���������� ����������
char i=0;
char array[4]= {0x3f,0x06,0x5b,0x4f};    //������ ������������ ������
int FI;
int flag;
/*SPI interrupt service routine - ������������ ��������� ���������� �� ���������� ����� ���������� ����� ������ �� SPI*/
interrupt [SPI_STC] void spi_isr(void)
{
unsigned char data;
data=SPDR;    //������ ���������� �����
if(data=='1') //���� ������ 1,������ ������ ����� �������
{
FI=0xFF;
flag=1;
}
if(data=='0') //���� ������ 0, ������ ������ ����� ���
{
FI=0x00;
flag=1;
}
if(flag==1)
{
if(FI==1)
{
PORTD=data;
flag=0;
}
else
{
PORTC=data;
flag=0;
}

} 

}

void main(void)
{
//Declare your local variables here

//Input/Output Ports initialization
//Port B initialization (PB4 �SS; PB5 � MOSI; PB7 � SCK)
//Func7=Out Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In
PORTB=0x00;
DDRB=0xB0;

PORTD=0xFF;
DDRB=0xFF;
PORTC=0xFF;
DDRB=0xFF;
//SPI initialization
//SPI Type: Master
//SPI Clock Rate: 500,000 kHz
//SPI Clock Phase: Cycle Start
//SPI Clock Polarity: High
//SPI Data Order: MSB First
SPCR=0xD9;
SPSR=0x00;
//Global enable interrupts
#asm("sei")
        /*����� �������'F'=0x46, ���������� �������� ������
                    ���������� � ������� ��������� ���������� SPI*/
while (1)
    {
    }
}
