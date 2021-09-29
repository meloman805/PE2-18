/*********************************************************
Chip type               : ATmega328P
AVR Core Clock frequency: 16,000000 MHz
Формирование периодической импульсной последовательности:
|--|____|------|________|--|____
10u 20u   30u     40u    
 <--------- T --------->
Количество интервалов в периоде должно быть чётным!!!
Для переключения длительности интервалов используется 
прерывание по совпадению канала 0A. Модуль счета также - 
в регистре OCR0A.
**********************************************************/
#include <mega328p.h>

// Declare your global variables here
unsigned char interval=0;
// Timer 0 output compare A interrupt service routine
interrupt [TIM0_COMPA] void timer0_compa_isr(void)
{
// Place your code here
switch (interval) 
   {
    case 0 :  OCR0A=39; interval=1; break;
    case 1 :  OCR0A=59; interval=2; break;   
    case 2 :  OCR0A=79; interval=3; break;   
    default:  OCR0A=19; interval=0; break;
    };
}

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port D initialization
// Function: Bit7=In Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 2000,000 kHz
// Mode: CTC top=OCR0A
// OC0A output: Toggle on compare match
// OC0B output: Disconnected
// Timer Period: 0,01 ms
// Output Pulse(s):
// OC0A Period: 0,02 ms Width: 0,01 ms
TCCR0A=(0<<COM0A1) | (1<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (1<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (0<<CS02) | (1<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0A=19;
OCR0B=0;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=(0<<OCIE0B) | (1<<OCIE0A) | (0<<TOIE0);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      }
}

