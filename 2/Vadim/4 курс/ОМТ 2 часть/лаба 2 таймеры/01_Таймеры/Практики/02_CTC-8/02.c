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
// Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=0 State2=T State1=T State0=T 
PORTB=0x00;         //PB3 - на вывод данных
DDRB=0x08;          //Это выход схемы сравнения OC0

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 1000,000 kHz
// Mode: CTC top=OCR0
// OC0 output: Toggle on compare match
TCCR0=0x1A;
TCNT0=0x00;
OCR0=0x00;

while (1)
      {
      // Place your code here
      OCR0=PINA;    //Пишем в регистр сравнения OCR0 код на выводах порта A
      }             //Задавая тем самым период меандра
}
