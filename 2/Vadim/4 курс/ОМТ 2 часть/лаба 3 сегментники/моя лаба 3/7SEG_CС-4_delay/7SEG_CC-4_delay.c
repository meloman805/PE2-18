#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//���������� ������� 10 ���������� ���� (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������
unsigned char BCD_MASS[4]={0,0,6,7};
unsigned char BCD_HIGHT[4]={0,1,7,6};
void main(void)
{
// Input/Output Ports initialization

// Port B initialization PB.3...PB.0 - �� ����� ������
PORTB=0x00;
DDRB=0x0F;

// Port C initialization PortC - �� ����� ������
PORTC=0x00;
DDRC=0xFF;

//���� A
PORTA=0xFF;
DDRA=0xFF;

while (1)                                   //����������� ���� ������������ ���������
    {
    unsigned char i;                        //������ �������� ������� ������. ���. ����
    // Place your code here
       for (i=0;  i<4; i++)
            {
            PORTB=0b1000>>i;                //������������ ��������� ����� �����
            
                if(PINA)
                {
                PORTC=DIG_DEC[BCD_MASS[i]]; //��� 7-���. ������� ��� ���������� ���������� ����
                } 
                 else
                 {
                 PORTC=DIG_DEC[BCD_HIGHT[i]]; //��� 7-���. ������� ��� ���������� ���������� �����
                 }
            delay_us(2500);                 //�������� ��� ��������� ���������� ����������
            PORTB=0x00;                     //������� �������� ���������� (����� ������ ��� ���. PROTEUS)
            PORTC=0;                        //��� �������� � ������� ��� ������������� (���� ������
            delay_us(5);                    //�� ����� ������ ����������� ������� �������� ����������)
            }
    }
}

