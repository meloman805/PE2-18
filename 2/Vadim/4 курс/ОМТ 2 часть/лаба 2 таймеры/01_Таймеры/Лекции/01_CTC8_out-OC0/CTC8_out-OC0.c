#include <mega16.h>

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// »нициализаци€ разр€да порта B PB.3 на вывод с начальным нулевым значением
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (1<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=0 Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: CTC top=OCR0
// OC0 output: Toggle on compare match
// „астота меандра на выводе OC0 Fclk/[2*(OCR0+1)]=8ћ√ц/[2*(OCR0+1)]=500 к√ц
// ѕериод меандра на выводе OC0 [2*(OCR0+1)]/Fclk=[2*(OCR0+1)]/8ћ√ц=2 мкс
TCCR0=(0<<WGM00) | (0<<COM01) | (1<<COM00) | (1<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x07;

// «апрет всех прерываний от таймера
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

while (1)
      {
      // Place your code here

      }
}
