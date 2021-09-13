/*******************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 12,000000 MHz
арефмитическая функция реализованая в МК Atmega16
PORTC.0
*******************************************************/
#include <mega16.h>
#include <delay.h>
    #include <math.h>
// Переменные в SRAM
unsigned  char a@0x75;  
unsigned  char b@0x76;
unsigned  char c,d,f,g,result;
      int a1,b1;
// Переменный в FLSASH

flash int x=7;

// Переменные в EEPROM

eeprom int y=25;

unsigned  char _sqrt(unsigned  char x) {
int y0 = 0;
int y1 = 0xFFFF;
while (y1 - y0 > 1) {
int y = (y0 + y1) >> 1;
int y2 = y * y;
if (y2 == x) return y;
if (y2 > x) y1 = y;
else y0 = y;
}
return (y0 + y1) >> 1;
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
//Обработчик прерывания, увеличивающий counter при клике кнопки

}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
DDRA=0b11111111;    //PORTA - все биты на вывод данных
PORTA=0b00000000;

// Port C initialization
DDRC=0b00000001;        //младший бит PORTC - на вывод
PORTC=0b00000000;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Rising Edge
// INT1: Off
// INT2: Off
GICR|=(0<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(0<<ISC11) | (0<<ISC10) | (1<<ISC01) | (1<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(0<<INTF1) | (1<<INTF0) | (0<<INTF2);
    a=4;
    b=2;
    c=3;
    d=4;
    f=5;
    g=1;
    y=8;
    
// Global enable interrupts
#asm("sei")
   result=pow(a,2); //    result=(sqrt(a))+(2*a*g)+(sqrt(g))-(pow((a*b),2));
      PORTB=result;
       result+=(2*a*g);
        PORTB=result;
          result+=g*g;  
          PORTB=result;
            a1=(pow(a*b,0.5));      
          result-=a1;
            PORTB=result;
             delay_ms(250);
while (1)
    
      delay_ms(250);

}
