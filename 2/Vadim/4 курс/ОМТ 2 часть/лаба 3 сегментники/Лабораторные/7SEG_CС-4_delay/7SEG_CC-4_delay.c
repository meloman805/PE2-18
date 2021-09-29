#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//библиотека графики 10 десятичных цифр (знакогенератор)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//число в распакованном BCD (одна цифра в одном байте), ст. байт по младшему адресу
unsigned char BCD_UNPACKED[4]={1,2,3,4};
void main(void)
{
// Input/Output Ports initialization

// Port B initialization PB.3...PB.0 - на вывод данных
PORTB=0x00;
DDRB=0x0F;

// Port C initialization PortC - на вывод данных
PORTC=0x00;
DDRC=0xFF;

while (1)                                   //бесконечный цикл динамической индикации
    {
    unsigned char i;                        //индекс элемента массива распак. дес. цифр
    // Place your code here
       for (i=0;  i<4; i++)
            {
            PORTB=0b1000>>i;                //Активизируем очередной общий катод
            PORTC=DIG_DEC[BCD_UNPACKED[i]]; //Код 7-сег. дисплея для очередного знакоместа
            delay_us(2500);                 //Задержка для подсветки очередного знакоместа
            PORTB=0x00;                     //Гашение текущего знакоместа (нужно только для инд. PROTEUS)
            PORTC=0;                        //Для реальных в гашении нет необходимости (если только
            delay_us(5);                    //не стоит задача регулировки яркости свечения индикатора)
            }
    }
}

