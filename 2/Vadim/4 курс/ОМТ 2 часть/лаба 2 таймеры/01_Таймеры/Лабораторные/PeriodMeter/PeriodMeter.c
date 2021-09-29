//Системная тактовая частота 8 MHz
#include <mega16.h>
bit b=0;                    //декларация глобальной битовой переменной
// Timer1 input capture interrupt service routine, обработчик прерывания по захвату
interrupt [TIM1_CAPT] void timer1_capt_isr(void)
{
if (b==0)
        {
        TCCR1B=0xC2;        //Запуск T1 на счет с нулевого значения с делением на 8
        b=1;                //Изменение реакции на последующее прерывание
        }
else
        {
        TCCR1B=0xC0;        //Останов TC1
        PORTA=ICR1L;        //Вывод регистра захвата ICR1
        PORTB=ICR1H;        //в порты A и B
        TCNT1H=0x00;        //Обнуление таймера TC1 для последующих измерений
        TCNT1L=0x00;
        b=0;                //Изменение реакции на последующее прерывание
        };
}

void main(void)             //главная функция
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization, PORTA - на вывод с начальными нулевыми битами
PORTA=0x00;
DDRA=0xFF;

// Port B initialization, PORTB - на вывод с начальными нулевыми битами
PORTB=0x00;
DDRB=0xFF;

// Port C initialization, PORTC - на ввод без подтягивающих резисторов
PORTC=0x00;
DDRC=0x00;

// Port D initialization, PORTD - на ввод без подтягивающих резисторов
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: On
// Input Capture on Rising Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: On
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0xC0;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<TICIE1;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=1<<ACD;
SFIOR=0x00;

// Global enable interrupts
#asm("sei")

while (1)       //Бесконечный цикл
      {
      };
}
