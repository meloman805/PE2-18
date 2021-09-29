/**********************************************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
���������� ������������ ����� � ������������� � ������� �� ����
����������� ��������� ���������� ����� � ��� �� ��� ������������ � ����������� 
����� ������� ���������.
��������� ������������ ����� ������������ � ������� �������� ���������� INT2
(�� ����� - ����������� ������� ��������� � ��������� �������� 1��� �������� TCNT0,
�� ������ - ���� ��������������� � ���������� TCNTO ������������ � ���������� 
���������� pause, �������� ������� ������� ���������� ��������� �� ����).
����� ������������ ������� ������� ������������ overflow
***********************************************************************************/
#include <mega16.h>
#include <stdio.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
unsigned char pause;            //������������ ����� � ����� ���������� �����������
bit overflow;                   //������� pause>255 ��� 
char string_lcd1[17];           //��������� ����� ��� 1-�� ������ LCD ������� ����-����������
char string_lcd2[17];           //��������� ����� ��� 2-�� ������ LCD ������� ����-����������

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
// Place your code here
if (MCUCSR==0x00) 
        {
        TCCR0=0x02;     //������ TCNT0 �� ���� �� 0 � NORMAL c f=1���
        MCUCSR=0x40;    //��������� ���������� INT2(����� �����) - �� ������
        }
else  
        {
        TCCR0=0x00;     //������� TCNT0
        PORTA=TCNT0;    //����� TCNT0 � ���� A 
        pause=TCNT0;
        overflow=0;     //����� �������� ������������
        TCNT0=0;        //����� TCNT0 ��� ������. � ����. ��������� 
        MCUCSR=0x00;    //����. ���������� INT0 - �� �����
        };
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
PORTA=0xFF;             //����� �� ��������� 0xFF � ������ ������������
overflow=1;             //��������� �������� ������������ pause > 255
TCCR0=0x00;             //������� TCNT0
TCNT0=0;                //����� TCNT0 ��� ������. � ����. ��������� 
MCUCSR=0x00;            //����. ���������� INT0 - �� �����
}

void main(void)
{
// Input/Output Ports initialization
PORTA=0x00;
DDRA=0xFF;              //� ���� � ����� ���������� �������� ��� 

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: On
// INT2 Mode: Falling Edge
GICR|=0x20;
MCUCR=0x00;
MCUCSR=0x00;            //���������� INT2 - �� �����
GIFR=0x20;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;             //���������� ���������� �� ������������ TCNT0

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTD Bit 2
// RD - PORTD Bit 1
// EN - PORTD Bit 3
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
lcd_init(16);
lcd_clear();
sprintf (string_lcd1,"Measuring Pause time");   //������������ ���������� ������ ��� 1-�� ������ LCD
lcd_puts(string_lcd1);                          //������� �� LCD 1-� ������ ������
// Global enable interrupts
#asm("sei")

while (1)               //���� ��������� �� LCD ���������� pause
      {
      // Place your code here
      if (overflow) 
            sprintf (string_lcd2,"Tpause > 255 mks");       //����� ���������������� ���������
      else 
            sprintf (string_lcd2,"Tpause=%3u mks  ",pause);  //������������ ���������� ������ ��� 2-�� ������ LCD 
      lcd_gotoxy (0, 1);                        //������� �� 1-�� ���������� 2-�� ������
      lcd_puts(string_lcd2);                    //����� ���������� ����� �� LCD
      }                                         //� ��������� ��� ������
}