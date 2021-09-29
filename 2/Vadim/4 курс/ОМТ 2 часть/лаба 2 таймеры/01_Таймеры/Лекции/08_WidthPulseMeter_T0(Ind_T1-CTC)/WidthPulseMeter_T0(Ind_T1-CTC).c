#include <mega16.h>
#include <delay.h>
#include <bcd.h>            //������������ ������� �������������� ��. ����� (0...99) � ����������� BCD
// Declare your global variables here
//���������� ������� 10 ���������� ���� (��������������)
flash unsigned char  DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//����� � ������������� BCD (���� ����� � ����� �����), ��. ���� �� �������� ������
unsigned char BCD_UNPACKED[4]={0,0,0,0};    //� �������� ��������� �� ���������� 0000
/*����� znakomesto � i - ����������, ���������� � ��� ������ ���� ������ �� ����������� ���������� T1*/
unsigned char i=0;                           //������ ��������� ������� ����. ���. ����

//////////External Interrupt 1 service routine, ���������� �������� ���������� �� ����� INT1//////////
interrupt [EXT_INT1] void ext_int1_isr(void)
{
if (MCUCR==0x0C)    {
                    MCUCR=0x08;     //�������� ��� ���������� - �� �����
                    TCCR0=0x02;     //���� ���������� ���� �� ������ - ��������� T0
                    }
else                {
                    //�������� ����� � ��� ���������� ������� - ����������� ����� ��� �����
                    unsigned char sot=0, bin_time;
                    TCCR0=0x00;     //���� ���������� �� ����� - ���������� T0
                    bin_time=TCNT0; //����� � �������� ���� ��������� ��� ������. ��������������
                    PORTA=TCNT0;    //������� ����� � ��� � ��. ���� � PORTA
                    TCNT0=0x00;     //�������� TCNT0 ��� ����������� ���������
                    MCUCR=0x0C;     //�������� ��� ���������� - �� ������, ������ �������������� � ������. BCD


                    sot=0;
                    while (bin_time>=100)   //�������� ������� �����
                        {
                        bin_time-=100; sot++;
                        };                          //����� � bin_time �������� ����� ������ (0...99)
                    sot=bin2bcd(sot);               //������� ����������� BCD-��� ����� ����� (0...99)
                    bin_time=bin2bcd(bin_time);     //������� ����������� BCD-��� ����� ������ (0...99)
                    BCD_UNPACKED[0]=sot>>4;         //�������� ������������� BCD ����� ����� (0...9)
                    BCD_UNPACKED[1]=sot&0x0F;       //�������� ������������� BCD ����� ����� (0...9)
                    BCD_UNPACKED[2]=bin_time>>4;    //�������� ������������� BCD ����� �������� (0...9)
                    BCD_UNPACKED[3]=bin_time&0x0F;  //�������� ������������� BCD ����� ������ (0...9)
                    };
}
////////// Timer1 output compare A interrupt service routine, ���. ����. �� ����. A TC1//////////
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{                   //�������� ����� TC1 �� ���� - �� ��� ��������� ��� ���������� � ��������� ���������� (����� CTC)
PORTB=0x00;         //������� �������� ����������, ���������� ��� ������ PROTEUS
PORTC=0x00;         //��� ��������� ���������� �������������
//delay_us(50);
PORTB=0b1000>>i;                    //�������� �������� ���� ���������� ����������
PORTC=DIG_DEC[BCD_UNPACKED[i]];     //��� ����� 7-���. ������� ��� ���������� ����������
i++;                //��������� � ����. ���������� ����� � ����. ����������
if (i>3) i=0;       //���� ������ ��� ����������, �������� ���� ���. ���. �������
}

////////////////////������� �������////////////////////
void main(void)
{
// Declare your local variables here

PORTA=0x00;
DDRA=0xFF;                          //���� A - �� �����, ����� � ���� �����

PORTB=0x00;
DDRB=0x0F;                          //4 ��. ������� PORTB - �� �����

PORTC=0x00;
DDRC=0xFF;                          //���� � - �� �����, ����� � ���� �����

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;                         //������ T0 ���������� � ������� ���������
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x09;        //������ ������� � ����. �������� � ���. CTC
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x4E;        //�������� �������� ��������� ������, ��������������
OCR1AL=0x20;        //���� �� ���� �� ���������� � ������� 2,5 �� (������� ��������� 100 ��)
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x10;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=0x80;                         //���������� �������� ���������� INT1
MCUCR=0x0C;                         //������ ����. - �������� ����� �� ����� INT1
MCUCSR=0x00;
GIFR=0x80;

// Global enable interrupts
#asm("sei")

while (1)                               //����������� ���� (������� ���������)
      {                                 //����� ��������� ��������� ���������� � ����������� ���������� �� ���������� A timer1_compa_isr
      // Place your code here
      };
}
