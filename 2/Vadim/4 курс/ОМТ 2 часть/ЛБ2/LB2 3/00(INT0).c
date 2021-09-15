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
// asm
// (
//    .DSEG     
//    .ORG 0x0000
//    g:	.db  	1,2,3  
//    .CSEG
//    );

unsigned  char a1@0x75;  
unsigned  char b1@0x76;
    int i=0;

// ���������� � FLSASH

flash int x=7;
  float s[4];
// ���������� � EEPROM
 eeprom float a[4]={1,2,3,4};
 eeprom  float *adr=&a[0];
 //���������� � ���
  float b[4];
 

 void calc(float *arr);



void calc(float *arr)
{
register int t;
for(t=0; arr[t]; ++t)
{
int x= a[t];
arr[t] = tan((x)/5);

}
}
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
 





 
    
// Global enable interrupts
#asm("sei")
//  
 

  
  calc(b);

//for (i=0;i<4;i++) {
//// b[i]=s[i]
//    };
while (1)
 {
      delay_ms(250);

}
}