/*****************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
*****************************************************/
#include <mega16.h>

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Port B initialization
PORTB=0x00;     //PB3 - на вывод
DDRB=0x08;      //это выход схемы сравнени 0 - OC0

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Normal top=0xFF
// OC0 output: Toggle on compare match
TCCR0=0x11;
TCNT0=0x00;
OCR0=0x80;

while (1)
      {
      }
}
