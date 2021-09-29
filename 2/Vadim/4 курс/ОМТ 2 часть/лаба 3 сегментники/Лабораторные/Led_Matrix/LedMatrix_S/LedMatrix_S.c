/*��������� ������������� ������� �� ������� �����������. ����� ��� �����������
��������� �������� ������������ ������������ ������� delay_ms*/
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

//Declare your global variables here
//������� ����� ��� ���� 4-� ������, ����� ��������� ����� ���������� ����� ��������� �����
char A[13] = {0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x40,0x00,0x00,0x00};
char B[13] = {0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x80,0x00,0x00};
char C[13] = {0x00,0x00,0x00,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x80,0x00};
char D[13] = {0x00,0x00,0x00,0x00,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x40};

void main(void)
{
// Declare your local variables here
char i;
// Input/Output Ports initialization
// Port A initialization
//PORTA=0x00;           //POPTA - �� ����� ������
DDRA=0xFF;

// Port B initialization
//PORTB=0x00;           //POPTB - �� ����� ������
DDRB=0xFF;

// Port C initialization
//PORTC=0x00;           //POPTC - �� ����� ������
DDRC=0xFF;

// Port D initialization
//PORTD=0x00;           //POPTD - �� ����� ������
DDRD=0xFF;

while (1)
      {
      // Place your code here

      for (i=0;i<13;i++)
            {
            PORTA|=A[i];            //� ��������� ��� - ������������� �����
            PORTB|=B[i];            //������� ����������� ����� ��������� ����������
            PORTC|=C[i];            //��� �������� ��� (������� ������������ ���������
            PORTD|=D[i];            //������� - ������� ����� �� ������� �������
            delay_ms(250);
            };
      PORTA=0x00;                   //����� ��� ���������� �� �������� �����
      PORTB=0x00;                   //��������
      PORTC=0x00;
      PORTD=0x00;
      delay_ms(250);
      }                             //� ����� �������� ���� �������
}                                   //����� ������� �������
