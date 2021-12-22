/*******************************************************
Chip type               : ATmega328P
AVR Core Clock frequency: 16,000000 MHz
*******************************************************/
#include <mega328p.h>
#include <delay.h>
// Declare your global variables here
//����������� ����� ������ ��� SPI �� Atmega328p
#define SS PORTB2
#define SCK PORTB5
#define MOSI PORTB3

//����������� ������� �������������� ��������� max7219
#define Intensity   0x0A        // ������������� �������� �������
#define ScanLimit   0x0B        // ����������� ����� ��������
#define ShutDown    0x0C        // �������� �������
#define DecodeMode  0x09        // ����� �������������

long int freq;
   char i; 
   int a; 
void SET(char addr, char data);
interrupt [EXT_INT0] void ext_int0_isr(void)
{
    freq++;  
}

interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
// TCNT1H=0x00;
//TCNT1L=0x00;
freq=0;

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
}


// Timer1 output compare A interrupt service routine, ���������� ���������� �� ���������� A
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10); //���������� ��������
//TCNT1H=0x00;        //��������� �������� �������� TC1
//TCNT1L=0x00;        //��� ����, ����� ����������� ��������� ���� ������
//OCR1AH=0x0B;
//OCR1AL=0xDC;

 for(i=0;i<8;i++) 
 {
 SET(i+1,i);
 
 } 
 freq=0;
}



/*������� �������� ����� �� SPI-���������� �� MASTER-����������(��)*/
void SPI_MasterTransmit(char d) //� ���������� d ��������� ���� ��� �������� �� SPI ����������
  {
  SPDR = d;                     //�������� ���� � ��������� ������� SPDR
  while(~SPSR & (1<<SPIF));     //���� ���� �������� 1 � ������� SPIF (7) �������� 
                                //SPSR - ������� ���������� �������� �����
  }                             //���� ������� ���������� Slave, �������

/*������� �������� ������ � ������ ��� MAX7219 �� SPI-����������*/
void SET(char addr, char data)
{
PORTB&=~(1<<SS);    //�� /SS ���������� 0 ��� ������ �������� ���������� (MAX7219)
//���������� �� SPI ������� ����, ���������� � ������� ������� ����� ��������������� ��������, 
SPI_MasterTransmit(addr);       //���������� �� SPI addr:
//���������� ������� ���� - ������ ������ 
SPI_MasterTransmit(data);       //���������� �� SPI data
//�� /SS ���������� 1, �.�. ��������� MAX7219 � ������������ ���������� � �� 16-������ �����
PORTB|=(1<<SS);                 
}



/*������� �������*/
void main(void)
{
// Declare your local variables here


// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Low level
// INT1: On
// INT1 Mode: Rising Edge
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=(1<<ISC11) | (1<<ISC10) | (0<<ISC01) | (0<<ISC00);
EIMSK=(1<<INT1) | (1<<INT0);
EIFR=(1<<INTF1) | (1<<INTF0);
PCICR=(0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif


// Timer/Counter 0 initialization
// Clock source: T0 pin Rising Edge
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
TCCR0B=(0<<WGM02) | (1<<CS02) | (1<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 16000,000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 1 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0xFF;// 0x3E
OCR1AL=0x7F;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (1<<OCIE1A) | (0<<TOIE1);

/*��������� ���������*/
// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=Out Bit2=Out Bit1=In Bit0=In
// �������� ����� ���. SPI:   PB5-SCK;               PB3-MOSI;    PB2-/SS 
DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=0 Bit2=0 Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 2*4000,000 kHz - ����������� ��������� �������� �������� �� SPI ��� ������� ��
// SPI Clock Phase: Cycle Start
// SPI Clock Polarity: Low
// SPI Data Order: MSB First
SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
SPSR=(1<<SPI2X);

// ������������� Max7219
SET(Intensity, 0x03);      // ��������� ������������� �������� (�� 0 �� F)
SET(ScanLimit, 0x07);      // ��������� ���� 8 ��������� 7SEG ���������
SET(ShutDown, 1);          // ��������� ������ ���������, � �� ���������� 
SET(DecodeMode, 0xFF);     // ��������� ������ ������������� (� �������������� ���������� ����������������)

#asm("sei");
while (1)
    {
   
    }        

}
