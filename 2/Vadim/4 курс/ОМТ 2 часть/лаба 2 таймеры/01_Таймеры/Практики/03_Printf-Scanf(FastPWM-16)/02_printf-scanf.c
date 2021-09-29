#include <mega16.h>
// Standard Input/Output functions
#include <stdio.h>

// Declare your global variables here
float f=1.234567;
unsigned int i=15; 
int j=0x0A;
unsigned char k=123;
void main(void)
{
PORTA=0x00;
DDRA=0xFF;
PORTB=0x00;
DDRB=0xFF;

// Port D initialization
// Func7=In Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=0 State4=0 State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x30;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Fast PWM top=ICR1
// OC1A output: Non-Inv.
// OC1B output: Inverted
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0xB2;
TCCR1B=0x19;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0xFF;         //Задание максимальной вершины счета (TOP)
ICR1L=0xFF;         //в режиме fast PWM
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
printf("TEST terminal output-input\n\r");
printf("i=%u j=%d k=%u f=%f\n\r", i, j, k, f);
//printf("Input float f=");
//scanf("%f",&f);   //Нет ввода значений float (только int и long)
//printf("f=%f\n\r",f);
while (1)
      {
      printf("Input  integer 1-65535 for OCR1A, OCR1B ");
      scanf("%d",&i);
      j=i>>8;       //в j - старший байт i
      OCR1AH=j; OCR1BH=j; OCR1AL=i; OCR1BL=i;
      }
}
