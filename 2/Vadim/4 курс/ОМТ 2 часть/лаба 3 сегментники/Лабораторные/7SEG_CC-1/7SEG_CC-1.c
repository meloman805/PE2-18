#include <mega16.h>

//���������� ������� 10 ���������� ���� 0...9 (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
char i=9;           //�����, ��������� �� ���������

void main(void)
{
// Port C initialization
//Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
PORTC=0x00;
DDRC=0xFF;

// Port B initialization
//Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=In Func1=In Func0=In
PORTB=0x00;
DDRB=0b00001000;

PORTC = DIG_DEC[i]; /*�������� � PORTC ���� ������� ����� "9"
                    �� ������� ���������� ������� ���������� ���� dig_dec[i]*/
PORTB = 0b00001000; //��������� ��������� �����

while(1);           //����������� ����

}
