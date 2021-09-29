/************************************************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
���������� ������������ ����� ������������� ���������� ������������������ � ���
������������ ��������� ������������ � ������� ���������� �� ������� TCNT2
�� ���������� � ������ CTC, ������������� ����� ������ 2.5 �� (������������ 
��������� ������ ����������).
��������� ������������ ����� ������������ � ������� �������� ���������� INT0
(�� ����� - ����������� ������� ��������� � ��������� �������� 1��� �������� TCNT0,
�� ������ - ���� ��������������� � ���������� TCNTO ������������� � �������-����������
4-���������� ������������� ��� ������������ ����� � �������������, ������� ������������ 
���������� �� ���������� TCNT2 ��������� �� 4-���������� �������������� ���������).
������� ��������� - ������ ����������� ����, ����������� ������������� ����������.
*************************************************************************************/
#include <mega16.h>
#include <bcd.h>        //����������� ���������� �������-���������� ��������������
// Declare your global variables here
//���������� ������� 10 ���������� ���� � "-" ��� ������������ (��������������)
//////////////////////////0////1////2////3////4////5////6////7////8////9////-//
flash char DIG_DEC[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
//����� ��� � ����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //� ���. ����. �� ���. 0000
unsigned char n_znak;                       //����� ��������������� ����������, ����� ����������
                                            //����������, ��������� ������������ ����������
// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
if (MCUCR==0x02) 
        {
        TCCR0=0x02;     //������ TCNT0 �� ���� �� 0 � NORMAL c f=1���
        MCUCR=0x03;     //��������� ���������� (����� �����) - �� ������
        }
else  
        {
        unsigned char sot=0, pause;
        TCCR0=0x00;     //������� TCNT0
        PORTA=TCNT0;    //����� TCNT0 � ���� A
        pause=TCNT0;    //� � ���������� pause
        TCNT0=0;        //����� TCNT0 ��� ������. � ����. ��������� 
        MCUCR=0x02;     //����. ���������� INT0 - �� �����
        while (pause>=100) 
            {
            pause-=100, sot++;
            };          //����� � sot - ���������� ����� ����������� (<=99), � pause - ���-�� ����������� (<=99)
        sot=bin2bcd(sot);       //������������ ������� �������������� � ����������� BCD, ����� ������ � �����
        pause=bin2bcd(pause);   //����� ������� � �������
        //��������� �������������� BCD ���� ���� �� ������������
        BCD_UNPACKED[0]=sot>>4, BCD_UNPACKED[1]=sot&0x0F, BCD_UNPACKED[2]=pause>>4,BCD_UNPACKED[3]=pause&0x0F; 
        };
}

// Timer 0 overflow interrupt service routine - ��������� "----" � ������ ������������
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
unsigned char i;
PORTA=0xFF;             //����� �� ��������� � ���� A 0xFF � ������ ������������
for (i=0;i<4;i++) 
    {
    BCD_UNPACKED[i]=10; //��� ����������� "-" �� 7SEG, 
    };                  // � ������ ������������ �� 7SEG ������������ "----"
TCCR0=0x00;             //������� TCNT0
TCNT0=0;                //����� TCNT0 ��� ������. � ����. ��������� 
MCUCR=0x02;             //����. ���������� INT0 - �� �����
}

// Timer2 output compare interrupt service routine - ����� ������������ �������������� ��������� ��� ������������ ���������
interrupt [TIM2_COMP] void timer2_comp_isr(void)
{
// ����� ���������� ��� ������������ ���������
PORTB=0xFF;                         //��������������� ������� �������� ���������� (��� ������ PROTEUS)
PORTB=~(0b00001000>>n_znak);        //�������� ����� ���������� ���������� (������ �������)
PORTC=DIG_DEC[BCD_UNPACKED[n_znak]];//��� ����� 7-���. ������� ��� ���������� ����������
n_znak++;                           //��������� � ����. ���������� ����� � ����. ����������
if (n_znak>3) n_znak=0;             //���� ������ ��� ����������, �������� ���� ���. ���. �������
}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
PORTA=0x00;
DDRA=0xFF;                  //���� A - �� ����� ������
PORTB=0xFF;
DDRB=0x0F;                  //���� B (������� 4 ����) - �� ����� ������
PORTC=0x00;
DDRC=0xFF;                  //���� C - �� ����� ������

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 31,250 kHz
// Mode: CTC top=OCR2
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x0E;
TCNT2=0x00;
OCR2=77;                   //��� ������ �������� OCR2 �������� ����� ������������ �� ���������� 
                           //� ������ CTC - (77+1)/31250=2.5 ��
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
TIMSK=0x81;                //���������� ����������: �� ������������ TCNT0 � �� ���������� TCNT2

// Global enable interrupts
#asm("sei")
while (1);
}
