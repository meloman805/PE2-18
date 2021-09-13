/*******************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 12,000000 MHz
*******************************************************/
#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//���������� ������� 16 ����������������� ���� (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9////A////B////C////D////E////F///
flash char GRAPH_HEX[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7C,0x39,0x5E,0x79,0x71};
unsigned int counter=0;     //������� ������� (������ ������)
//������ ��� ���� ����������������� ������������������ �����
unsigned char DIGITS[4]={0,0,0,0};
// External Interrupt 1 service routine ���������� �������� ���������� INT1
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
int i;
delay_ms(3);                //��������������� ��������
counter++;                  //��������� ��������
//���������� ���� ���� ������������������ ����� � ������ �� � ������ DIGITS[4], ������� �� �������
for (i=0;i<4;i++) 
    {
    DIGITS[i]=(((char)(counter>>(4*(3-i)))) & 0b00001111);  //���������� ��������� ����� ������������������ �����   
    };
GIFR|=0b10000000;       //����� ����� ���������� INT1, ������� ����������� �������� ��-�� ��������
}

void main(void)
{
// Declare your local variables here

// Port B initialization ������� ������� - �� ����� ��� ��������� �������� ������ (������ ���������)
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRB=0b00001111;
PORTB=0;

// Port C initialization �� ����� ��� ��������� ��������� ������� �����
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=0b11111111;
PORTC=0;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Falling Edge
// INT2: Off
GICR|=(1<<INT1) | (0<<INT0) | (0<<INT2);
MCUCR=(1<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
//GIFR=(1<<INTF1) | (0<<INTF0) | (0<<INTF2);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      unsigned char i;                      //������ �������� ������� ����������������� ����
      for (i=0; i<4; i++)                   //����������� �� ������� ���� ���� �����
            {
            PORTB=0b1000>>i;                //������������ ��������� ����� �����
            PORTC=GRAPH_HEX[DIGITS[i]];     //��� 7-���. ������� ��� ���������� ���������� (��������� �����)
            delay_ms(3);                    //�������� ��� ��������� ���������� ����������
            PORTB=0x00;                     //������� �������� ���������� (����� ������ ��� ���. PROTEUS)
            //PORTC=0;                        //��� �������� � ������� ��� ������������� (���� ������ 
            delay_us(5);                    //�� ����� ������ ����������� ������� �������� ����������)
            }
      }
}
