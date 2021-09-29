/***************************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
Формирование периодической импульсной последовательности:
|--|____|------|________|--|____
10u  20u   30u    40u
 <--------- T --------->
Количество интервалов в периоде должно быть чётным!!!

Для переключения длительности интервалов используется 
прерывание по совпадению канала 1A. Модуль счета также - 
в регистре OCR1A. Режим таймера 1 - СТС с вершиной счёта в OCR1A
***************************************************************/

#include <mega16.h>

// Declare your global variables here
unsigned char interval=0;
// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
// Place your code here
switch (interval) 
    {
    case 0 : OCR1AL=19; interval=1; break;
    case 1 : OCR1AL=29; interval=2; break;   
    case 2 : OCR1AL=39; interval=3; break;
    default: OCR1AL=9;  interval=0; break;
    };
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port D initialization
// Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (1<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 1000,000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Toggle on compare match
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 0,01 ms
// Output Pulse(s):
// OC1A Period: 0,02 ms Width: 0,01 ms
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (1<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=9;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
