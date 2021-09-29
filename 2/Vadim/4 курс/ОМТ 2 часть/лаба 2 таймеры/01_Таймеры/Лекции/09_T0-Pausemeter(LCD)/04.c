/**********************************************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
Измеритель длительности паузы в микросекундах с выводом на ТЖКИ
Циклическая индикация измеренной паузы в мкс на ЖКИ организована в бесконечном 
цикле фоновой программы.
Измерение длительности паузы организовано с помощью внешнего прерывания INT2
(по срезу - запускается подсчет импульсов с эталонной частотой 1МГц таймером TCNT0,
по фронту - счет останавливается и содержимое TCNTO запоминается в глобальной 
переменной pause, значение которой фоновой программой выводится на ТЖКИ).
Здесь используется битовый признак переполнения overflow
***********************************************************************************/
#include <mega16.h>
#include <stdio.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
unsigned char pause;            //длительность паузы в целом количестве микросекунд
bit overflow;                   //признак pause>255 мкс 
char string_lcd1[17];           //текстовый буфер для 1-ой строки LCD включая нуль-терминатор
char string_lcd2[17];           //текстовый буфер для 2-ой строки LCD включая нуль-терминатор

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
// Place your code here
if (MCUCSR==0x00) 
        {
        TCCR0=0x02;     //Запуск TCNT0 на счет от 0 в NORMAL c f=1МГЦ
        MCUCSR=0x40;    //следующее прерывание INT2(конец паузы) - по фронту
        }
else  
        {
        TCCR0=0x00;     //Останов TCNT0
        PORTA=TCNT0;    //вывод TCNT0 в порт A 
        pause=TCNT0;
        overflow=0;     //сброс признака переполнения
        TCNT0=0;        //сброс TCNT0 для подгот. к след. измерению 
        MCUCSR=0x00;    //след. прерывание INT0 - по срезу
        };
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
PORTA=0xFF;             //Вывод на индикацию 0xFF в случае переполнения
overflow=1;             //установка признака переполнения pause > 255
TCCR0=0x00;             //Останов TCNT0
TCNT0=0;                //сброс TCNT0 для подгот. к след. измерению 
MCUCSR=0x00;            //след. прерывание INT0 - по срезу
}

void main(void)
{
// Input/Output Ports initialization
PORTA=0x00;
DDRA=0xFF;              //в порт А будет выводиться двоичный код 

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
GICR|=0x20;
MCUCR=0x00;
MCUCSR=0x00;            //прерывание INT2 - по срезу
GIFR=0x20;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;             //разрешение прерывания по переполнению TCNT0

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTD Bit 2
// RD - PORTD Bit 1
// EN - PORTD Bit 3
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
lcd_init(16);
lcd_clear();
sprintf (string_lcd1,"Measuring Pause time");   //Формирование текстового буфера для 1-ой строки LCD
lcd_puts(string_lcd1);                          //Выводим на LCD 1-ю строку текста
// Global enable interrupts
#asm("sei")

while (1)               //цикл индикации на LCD переменной pause
      {
      // Place your code here
      if (overflow) 
            sprintf (string_lcd2,"Tpause > 255 mks");       //вывод диагностического сообщения
      else 
            sprintf (string_lcd2,"Tpause=%3u mks  ",pause);  //Формирование текстового буфера для 2-ой строки LCD 
      lcd_gotoxy (0, 1);                        //переход на 1-ое знакоместо 2-ой строки
      lcd_puts(string_lcd2);                    //вывод измеренной паузы на LCD
      }                                         //и повторяем все заново
}