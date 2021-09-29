#include <mega16.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
char a = 0x35;              //��������� ������ � ����� �5�
char *str = " 'PROM_EL' ";  //��������� ������ �PROM_EL�
void main(void)
{

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16
// LCD module initialization
lcd_init(16);
//_lcd_ready();             //���� ������� � ���������� alcd ���
//_lcd_write_data(0x01);    //������� �����
//_lcd_write_data(0x02);    //������������� ������ � ������� ������� �������*/
_lcd_write_data(0x0f);      /*�������� �����, �������� ������, �����������
                            ������� ������ � ���� ��������� ����������*/
lcd_gotoxy(2,1);            //��������� ������ �� 3-� ���������� 2-�� ������
lcd_putchar (a);            //������� �� ����� ����� 5
lcd_puts(str);              // ������� �� ����� ������
while (1);
}
