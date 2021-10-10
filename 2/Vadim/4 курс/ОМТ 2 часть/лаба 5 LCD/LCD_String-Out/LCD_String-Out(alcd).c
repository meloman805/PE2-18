#include <mega16.h>
#include <stdio.h>
// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
int g=45;
float b=12.136;

  float result=2.643;

char a = 0x33;              //��������� ������ � ����� �3�

void main(void)
{
char str[15];  //��������� ������ �PROM_EL�
    char res[16];   
     float c=5.375; 
     sprintf (str,  "Goncharenko V ");
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


sprintf (res, "%4.3f  ", c);

lcd_gotoxy(0,0);            //��������� ������ �� 3-� ���������� 2-�� ������

lcd_puts(str);              // ������� �� ����� ������
lcd_putchar (a);            //������� �� ����� ����� 5

lcd_gotoxy(0,1); 
lcd_puts(res);
while (1);
}
