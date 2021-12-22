#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//����������� ����� ������ ��� SPI �� Atmega328p
#define SS PORTB4
#define SCK PORTB7
#define MOSI PORTB5
 void SET(char addr, char data);
//����������� ������� �������������� ��������� max7219
#define Intensity   0x0A        // ������������� �������� �������
#define ScanLimit   0x0B        // ����������� ����� ��������
#define ShutDown    0x0C        // �������� �������
#define DecodeMode  0x09        // ����� �������������

int FREQH=0;
int DISPL=0;
int i;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
 FREQH++;
 DISPL= FREQH;
 for(i=0;i<8;i++) 
 {
 SET(i+1,DISPL%10);
  DISPL= DISPL/10;
 } 
}

// External Interrupt 1 service routine, ���������� �������� ���������� INT1
interrupt [EXT_INT1] void ext_int1_isr(void)
{
FREQH=0;             //��������� �������� ������������ �������� ��������
TCNT0=0x00;         //������ ��0 � ����
TCCR0=0x07;         //� ������ ����� ��������� � �������� ����� PB0/T0
TCCR1B=0x05;        //������ ��1 - ������ ������������ ���
}

// Timer1 output compare A interrupt service routine, ���������� ���������� �� ���������� A
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
TCCR0=0x00;         //������� TC0
TCCR1B=0x00;        //������� TC1
TCNT1H=0x00;        //��������� �������� �������� TC1
TCNT1L=0x00;        //��� ����, ����� ����������� ��������� ���� ������
PORTA=TCNT0;        //����� � ���� A ������� � ������
TCNT2=FREQH;
PORTC=FREQH;
//SET(2,6);

}

// Declare your global variables here

/*������� �������� ����� �� SPI-���������� �� MASTER-����������(��)*/
void SPI_MasterTransmit(char d) //� ���������� d ��������� ���� ��� �������� �� SPI ����������
  {
  SPDR = d;                     //�������� ���� � ��������� ������� SPDR
  while(~SPSR & (1<<SPIF));     //���� ���� �������� 1 � ������� SPIF (7) �������� 
                                //SPSR - ������� ���������� �������� �����
  }                             //���� ������� ���������� Slave, �������

/*������� ������    �� ������ � ������ ��� MAX7219 �� SPI-����������*/
void SET(char addr, char data)
{
PORTB&=~(1<<SS);    //�� /SS ���������� 0 ��� ������ �������� ���������� (MAX7219)
//���������� �� SPI ������� ����, ���������� � ������� ������� ����� ��������������� ��������, 
SPI_MasterTransmit(addr);       //���������� �� SPI addr:
//���������� ������� ���� - ������ ������ 
SPI_MasterTransmit(data);       //���������� �� SPI data
//�� /SS ���������� 1, �.�. ��������� MAX7219 � ������������ ���������� � ��� 16-������ �����
PORTB|=(1<<SS);                 
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization, ��� ������� ����� A - �� ����� � �������� ���. ����������
PORTA=0x00;
DDRA=0xFF;


// Port B initialization
// Function: Bit7=Out Bit6=In Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(1<<DDB7) | (0<<DDB6) | (1<<DDB5) | (1<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=0 Bit6=T Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
PORTD=0x00;
DDRD=0x00;



// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;         //� �������� ��������� TC0 ���������� � �������
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;        //� �������� ��������� TC1 ���������� � �������
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x1E;        //��������� � ������� ��������� A ��������
OCR1AL=0x83;        //��� ������������ T��=1��� (7813)
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=1<<INT1;              //���������� �������� ���������� INT1
MCUCR=1<<ISC11 | 1<<ISC10;  //������ - �� ��������� ������
MCUCSR=0x00;
GIFR=1<<INTF1;				//����� ����� ����������

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);	//���������� ���������� �� ���������� A TC1 � ������������ TC0

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;


// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 2000,000 kHz
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
// Global enable interrupts
#asm("sei")         //���������� ����������

while (1)           //����������� ����
      { 
     
      };
}
