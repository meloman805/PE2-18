/*******************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 12,000000 MHz
�������������� ������� ������������ � �� Atmega16
PORTC.0
*******************************************************/
#include <mega16.h>
#include <delay.h>
    #include <math.h>
// ���������� � SRAM
unsigned  char a@0x75;  
unsigned  char b@0x76;
unsigned  char c,d,f,g,result;
      int a1,b1;
// ���������� � FLSASH

flash int x=240;

// ���������� � EEPROM

eeprom int y=25;



// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
//���������� ����������, ������������� counter ��� ����� ������

}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
DDRA=0b11111111;    //PORTA - ��� ���� �� ����� ������
PORTA=0b00000000;

// Port C initialization
DDRC=0b00000001;        //������� ��� PORTC - �� �����
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
    a=240;
    b=2;
    c=6;
    d=22;
    f=1;
    g=0;
    y=8;
    
// Global enable interrupts
#asm("sei")
   a1=tan(x); //    ��������� tg(x) 
      b1=    tan(a);   //    ��������� tg(a) 
       result=a1+b1;   //    ��������� tg(x)+tg(a)
        PORTB=result;//������� ������������� ���������
          result=result/b;  //��������� (tg(x)+tg(a))/b
           PORTB=result; //������� ����� � ����
             delay_ms(250);
while (1)
    
      delay_ms(250);

}
