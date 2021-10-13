/****************************************************
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>
//глобальные переменные
char i=0;
char array[4]= {0x3f,0x06,0x5b,0x4f};    //массив передаваемых данных

/*SPI interrupt service routine - подпрограмма обработки прерывания по завершению передачи очередного байта данных по SPI*/
interrupt [SPI_STC] void spi_isr(void)
{
if (i<5)                                //передача 4 байтов
{
SPDR =array[i];
i++;
}
//else SPСR=0x00;                       //Выключение SPI у ведущего МК
}

void main(void)
{
//Declare your local variables here

//Input/Output Ports initialization
//Port B initialization (PB4 –SS; PB5 – MOSI; PB7 – SCK)
//Func7=Out Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In
PORTB=0x00;
DDRB=0xB0;

//SPI initialization
//SPI Type: Master
//SPI Clock Rate: 500,000 kHz
//SPI Clock Phase: Cycle Start
//SPI Clock Polarity: High
//SPI Data Order: MSB First
SPCR=0xD9;
SPSR=0x00;
//Global enable interrupts
#asm("sei")

SPDR = 'F';         /*вывод символа'F'=0x46, дальнейшая передача данных
                    происходит в функции обработки прерывания SPI*/
while (1)
    {
    }
}
