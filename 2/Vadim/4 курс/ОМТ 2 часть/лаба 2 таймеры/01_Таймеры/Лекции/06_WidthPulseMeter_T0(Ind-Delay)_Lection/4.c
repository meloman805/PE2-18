#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//библиотека графики 10 десятичных цифр (знакогенератор)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//число в распакованном BCD (одна цифра в одном байте), ст. байт по младшему адресу
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //в исх. сост. на инд. 0000
// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
if (MCUCR==0x0C) 
                {
                TCCR0=0x02;     //запуск таймера на счет 
                MCUCR=0x08;     //Прерывание INt1 - по срезу
                }
else  
                {
                unsigned char sot=0, des=0, bin_time;
                TCCR0=0x00;     //останов счетчика
                PORTA=TCNT0;    //вывод измерения в порт A (в двоичном коде)
                bin_time=TCNT0; //время в мкс в двоичном коде
                TCNT0=0x00;     //обнуление счетчика для послед. измерений
                MCUCR=0x0C;     //Прерывание INT1 - по фронту
                while (bin_time>=100)       //начинаем считать сотни 
                        {
                        bin_time-=100; sot++;
                        }
                while (bin_time>=10)        //начинаем считать десятки
                        {
                        bin_time-=10; des++;
                        }                   //Здесь в BIN_TIME остаются единицы
                BCD_UNPACKED[1]=sot,  BCD_UNPACKED[2]=des, BCD_UNPACKED[3]=bin_time;                                 
                };             
}

void main(void)
{
// Port A initialization - вывод
PORTA=0x00;
DDRA=0xFF;
// Port С initialization - вывод
PORTC=0x00;
DDRC=0xFF;
// Port B initialization - 4 мл. разряда на вывод данных
PORTB=0xFF;
DDRB=0x0F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=0x80;
MCUCR=0x0C;
MCUCSR=0x00;
GIFR=0x80;

// Global enable interrupts
#asm("sei")

while (1)
      {
      unsigned char i;
      for (i=0;i<4;i++)
        {
        PORTB=0b11110111>>i;                //активиз. очередной общий катод
        PORTC=DIG_DEC[BCD_UNPACKED[i]];     //Графика очередного знакоместа (извлекаем из таблицы знакогенератора)
        delay_ms(5);                        //Задержка подсветки очередного знакоместа
        PORTB=0x0F;                         //Гашение сегментов очередного знакоместа перед переходом к след.
        PORTC=0;
        delay_us(50);                       //задержка гашения
        };

      };
}
