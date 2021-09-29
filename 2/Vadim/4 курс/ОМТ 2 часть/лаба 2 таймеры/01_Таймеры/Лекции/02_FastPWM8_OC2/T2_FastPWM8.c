#include <mega16.h>

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// ������������� 7-�� ������� ����� D (PD.7) �� ����� � �������� ��������� ���������
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(1<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Fast PWM top=0xFF
// OC2 output: Non-Inverted PWM
// Timer Period: 0,032 ms
// Output Pulse(s):
// OC2 Period: 0,032 ms Width: OCR2/Fclk=6,375 us
ASSR=0<<AS2;
TCCR2=(1<<PWM2) | (1<<COM21) | (0<<COM20) | (1<<CTC2) | (0<<CS22) | (0<<CS21) | (1<<CS20);
TCNT2=0x00;
OCR2=51;                            //����������� ���������� ��������� 0,2=51/256

// ������ ���� ���������� �� �������
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

while (1)
      {
      // Place your code here

      }
}
