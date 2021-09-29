/*************************************************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
���������� ������������ ����� ������������� ���������� ������������������
������������ ��������� ������������ � ����������� ����� ������� ���������.
��������� ������������ ����� ������������ � ������� �������� ���������� INT0
(�� ����� - ����������� ������� ��������� � ��������� �������� 1��� �������� TCNT0,
�� ������ - ���� ��������������� � ���������� TCNTO ������������� � �������-����������
4-���������� ������������� ��� ������������ ����� � �������������, ������� ������� 
���������� ��������� �� 4-���������� �������������� ���������).
*************************************************************************************/
#include <mega16.h>
#include <delay.h>      //����������� ���������� ��������
// Declare your global variables here
//���������� ������� 10 ���������� ���� � "-"  (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9////-//
flash char DIG_DEC[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
//����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //� ���. ����. �� ���. 0000
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
if (MCUCR==0x02) 
        {
        TCCR0=0x02;     //������ TCNT0 �� ���� �� 0 � NORMAL c f=1 ���
        MCUCR=0x03;     //��������� ���������� (����� �����) - �� ������
        }
else  
        {
        unsigned char sot=0, des=0, pause_bin;
        TCCR0=0x00;     //������� TCNT0
        PORTA=TCNT0;    //����� TCNT0 � ���� A � � ���������� pause_bin
        pause_bin=TCNT0;//����� � ������������� � �������� ����
        TCNT0=0;        //����� TCNT0 ��� ������. � ����. ��������� 
        MCUCR=0x02;     //����. ���������� INT0 - �� �����
        //��������� �������������� BCD �� pause_bin � ������ ��� � ������ BCD_UNPACKED[4] 
        while (pause_bin>=100)        //������� ����� � ����� 
            {
            pause_bin-=100; sot++;
            };           
        while (pause_bin>=10)        //������� �������� � ����� 
            {
            pause_bin-=10; des++;
            };                      //����� � pause_bin - ����� ������ (<=9)
        BCD_UNPACKED[0]=0, BCD_UNPACKED[1]=sot, BCD_UNPACKED[2]=des, BCD_UNPACKED[3]=pause_bin;         
        };
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
unsigned char i;
// Place your code here
PORTA=0xFF;             //����� �� ��������� � ���� A 0xFF � ������ ������������
for (i=0;i<4;i++) 
    {
    BCD_UNPACKED[i]=10; //��� ����������� "-" �� 7SEG, 
    };                  // � ������ ������������ �� 7SEG ������������ "----"
TCCR0=0x00;             //������� TCNT0
TCNT0=0;                //����� TCNT0 ��� ������. � ����. ��������� 
MCUCR=0x02;             //����. ���������� INT0 - �� �����
}

void main(void)
{
// Declare your local variables here
// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;
DDRA=0xFF;              //���� A - �� ����� ������
PORTB=0xFF;
DDRB=0x0F;              //���� B (������� 4 ����) - �� ����� ������
PORTC=0x00;
DDRC=0xFF;              //���� C - �� ����� ������

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=0x40;
MCUCR=0x02;
MCUCSR=0x00;
GIFR=0x40;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;             //���������� ���������� TCNT0 �� ������������

// Global enable interrupts
#asm("sei")

while (1)
      {                 //������� ��������� - ��������� ����������� ����� ����������� � �����                                      
      unsigned char i;  //�� �������������� ���������� � ����� ������� 7SEG-MPX4-CC
      for (i=0;i<4;i++)
        {
        PORTB=~(0b00001000>>i);             //�������. ��������� ����� ����� (������ �������)
        PORTC=DIG_DEC[BCD_UNPACKED[i]];     //������� ���������� ���������� (��������� �� ������� ���������������)
        delay_us(2500);                     //�������� ��������� ���������� ���������� 2.5 ��
        PORTB=0x0F;                         //������� ��������� ���������� ���������� ����� ��������� � ����.
        };
      };
}
