/*Программа вырисовывания символа на матрице светодиодов. Здесь для организации
временной задержки используется библиотечная функция delay_ms*/
/*****************************************************
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
#include <delay.h>

//Declare your global variables here
//массивы чисел для всех 4-х портов, число элементов равно количеству точек рисуемого знака
char A[13] = {0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x40,0x00,0x00,0x00};
char B[13] = {0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x80,0x00,0x00};
char C[13] = {0x00,0x00,0x00,0x01,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x80,0x00};
char D[13] = {0x00,0x00,0x00,0x00,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x40};

void main(void)
{
// Declare your local variables here
char i;
// Input/Output Ports initialization
// Port A initialization
//PORTA=0x00;           //POPTA - на вывод данных
DDRA=0xFF;

// Port B initialization
//PORTB=0x00;           //POPTB - на вывод данных
DDRB=0xFF;

// Port C initialization
//PORTC=0x00;           //POPTC - на вывод данных
DDRC=0xFF;

// Port D initialization
//PORTD=0x00;           //POPTD - на вывод данных
DDRD=0xFF;

while (1)
      {
      // Place your code here

      for (i=0;i<13;i++)
            {
            PORTA|=A[i];            //С операцией ИЛИ - вырисовывание знака
            PORTB|=B[i];            //стаются включенными ранее зажженные светодиоды
            PORTC|=C[i];            //без операции ИЛИ (простое присваивание элементов
            PORTD|=D[i];            //массива - бегущий огонь по контуру символа
            delay_ms(250);
            };
      PORTA=0x00;                   //гасим все светодиоды на заданное время
      PORTB=0x00;                   //задержки
      PORTC=0x00;
      PORTD=0x00;
      delay_ms(250);
      }                             //и затем начинаем цикл сначала
}                                   //конец главной функции
