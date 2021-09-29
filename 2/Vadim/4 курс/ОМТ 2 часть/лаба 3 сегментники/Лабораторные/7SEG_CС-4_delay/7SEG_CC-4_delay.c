#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//���������� ������� 10 ���������� ���� (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������
unsigned char BCD_UNPACKED[4]={1,2,3,4};
void main(void)
{
// Input/Output Ports initialization

// Port B initialization PB.3...PB.0 - �� ����� ������
PORTB=0x00;
DDRB=0x0F;

// Port C initialization PortC - �� ����� ������
PORTC=0x00;
DDRC=0xFF;

while (1)                                   //����������� ���� ������������ ���������
    {
    unsigned char i;                        //������ �������� ������� ������. ���. ����
    // Place your code here
       for (i=0;  i<4; i++)
            {
            PORTB=0b1000>>i;                //������������ ��������� ����� �����
            PORTC=DIG_DEC[BCD_UNPACKED[i]]; //��� 7-���. ������� ��� ���������� ����������
            delay_us(2500);                 //�������� ��� ��������� ���������� ����������
            PORTB=0x00;                     //������� �������� ���������� (����� ������ ��� ���. PROTEUS)
            PORTC=0;                        //��� �������� � ������� ��� ������������� (���� ������
            delay_us(5);                    //�� ����� ������ ����������� ������� �������� ����������)
            }
    }
}

