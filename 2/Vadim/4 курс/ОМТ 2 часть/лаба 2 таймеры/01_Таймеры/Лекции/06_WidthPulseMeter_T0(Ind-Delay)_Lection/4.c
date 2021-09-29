#include <mega16.h>
#include <delay.h>
// Declare your global variables here
//���������� ������� 10 ���������� ���� (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //� ���. ����. �� ���. 0000
// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
if (MCUCR==0x0C) 
                {
                TCCR0=0x02;     //������ ������� �� ���� 
                MCUCR=0x08;     //���������� INt1 - �� �����
                }
else  
                {
                unsigned char sot=0, des=0, bin_time;
                TCCR0=0x00;     //������� ��������
                PORTA=TCNT0;    //����� ��������� � ���� A (� �������� ����)
                bin_time=TCNT0; //����� � ��� � �������� ����
                TCNT0=0x00;     //��������� �������� ��� ������. ���������
                MCUCR=0x0C;     //���������� INT1 - �� ������
                while (bin_time>=100)       //�������� ������� ����� 
                        {
                        bin_time-=100; sot++;
                        }
                while (bin_time>=10)        //�������� ������� �������
                        {
                        bin_time-=10; des++;
                        }                   //����� � BIN_TIME �������� �������
                BCD_UNPACKED[1]=sot,  BCD_UNPACKED[2]=des, BCD_UNPACKED[3]=bin_time;                                 
                };             
}

void main(void)
{
// Port A initialization - �����
PORTA=0x00;
DDRA=0xFF;
// Port � initialization - �����
PORTC=0x00;
DDRC=0xFF;
// Port B initialization - 4 ��. ������� �� ����� ������
PORTB=0xFF;
DDRB=0x0F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=0x80;
MCUCR=0x0C;
MCUCSR=0x00;
GIFR=0x80;

// Global enable interrupts
#asm("sei")

while (1)
      {
      unsigned char i;
      for (i=0;i<4;i++)
        {
        PORTB=0b11110111>>i;                //�������. ��������� ����� �����
        PORTC=DIG_DEC[BCD_UNPACKED[i]];     //������� ���������� ���������� (��������� �� ������� ���������������)
        delay_ms(5);                        //�������� ��������� ���������� ����������
        PORTB=0x0F;                         //������� ��������� ���������� ���������� ����� ��������� � ����.
        PORTC=0;
        delay_us(50);                       //�������� �������
        };

      };
}
