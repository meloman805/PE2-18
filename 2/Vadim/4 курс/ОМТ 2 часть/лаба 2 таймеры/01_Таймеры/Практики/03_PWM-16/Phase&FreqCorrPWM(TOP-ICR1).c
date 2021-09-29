/*******************************************************
Chip type               : ATmega16
AVR Core Clock frequency: 8,000000 MHz
Phase&Frequency Correct PWM, для задания периода (ICR1) и 
коэффициента заполнения (OCR1) используем только младший 
байт соответствующего регистра, старшие байты нулевые.
*******************************************************/

#include <mega16.h>
// Declare your global variables here
void main(void)
{
// Input/Output Ports initialization
// Port D initialization - разряды PORTD выходов схем сравнения OC1B и OC1A - на вывод
// Function: Bit7=In Bit6=In Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (1<<DDD5) | (1<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7)|(0<<PORTD6)|(0<<PORTD5)|(0<<PORTD4)|(0<<PORTD3)|(0<<PORTD2)|(0<<PORTD1)|(0<<PORTD0);

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000,000 kHz
// Mode: Ph. & fr. cor. PWM top=ICR1
// OC1A output: Non-Inverted PWM
// OC1B output: Inverted PWM
// Коэффициент заполнения неинвертированного (на вых. OC1A) и инвертированного (на вых. OC1B)
// будет определяться соответственно содержимым регистров OCR1A и OCR1B
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 0 us
// Output Pulse(s):
// OC1A Period: 0 us
// OC1B Period: 0 us
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

while (1)
      {
      OCR1AL=PINA;      //определяет коэффициент заполнения ШИМ-сигналов
      OCR1BL=PINA;     
      ICR1L=PINB;       //определяет период ШИМ-сигнала
      }
}
