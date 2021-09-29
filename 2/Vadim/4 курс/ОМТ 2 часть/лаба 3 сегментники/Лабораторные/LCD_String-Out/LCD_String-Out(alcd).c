#include <mega16.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
char a = 0x35;              //выводимый символ Ц цифра Ђ5ї
char *str = " 'PROM_EL' ";  //выводима€ строка ТPROM_ELТ
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
//_lcd_ready();             //этой функции в библиотеке alcd нет
//_lcd_write_data(0x01);    //очищаем экран
//_lcd_write_data(0x02);    //устанавливаем курсор в нулевую позицию диспле€*/
_lcd_write_data(0x0f);      /*¬ключаем экран, включаем курсор, изображение
                            курсора делаем в виде мигающего знакоместа*/
lcd_gotoxy(2,1);            //переводим курсор на 3-е знакоместо 2-ой строки
lcd_putchar (a);            //выводим на экран цифру 5
lcd_puts(str);              // выводим на экран строку
while (1);
}
