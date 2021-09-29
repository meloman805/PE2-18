#include <mega16.h>

// External Interrupt 1 service routine, обработчик внешнего прерывания INT1
interrupt [EXT_INT1] void ext_int1_isr(void)
{
TCNT0=0x00;         //запуск ТС0 с нуля
TCCR0=0x07;         //в режиме счета импульсов с внешнего входа PB0/T0
TCCR1B=0x05;        //Запуск ТС1 - начало формирования Тэт
}

// Timer1 output compare A interrupt service routine, обработчик прерывания по совпадению A
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
TCCR0=0x00;         //Останов TC0
TCCR1B=0x00;        //Останов TC1
TCNT1H=0x00;        //Обнуление счетного регистра TC1
TCNT1L=0x00;        //для того, чтобы последующее измерение было верным
PORTA=TCNT0;        //Вывод в порт A частоты в герцах
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization, Все разряды порта A - на вывод с нулевыми нач. значениями
PORTA=0x00;
DDRA=0xFF;

// Port B initialization
PORTB=0x00;
DDRB=0x00;

// Port C initialization
PORTC=0x00;
DDRC=0x00;

// Port D initialization
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;         //в исходном состоянии TC0 остановлен и обнулен
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
TCCR1B=0x00;        //В исходном состоянии TC1 остановлен и обнулен
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x1E;        //Занесение в регистр сравнения A значения
OCR1AL=0x85;        //для формирования Tэт=1сек (7813)
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Rising Edge
// INT2: Off
GICR|=1<<INT1;              //Разрешение внешнего прерывания INT1
MCUCR=1<<ISC11 | 1<<ISC10;  //Запуск - по переднему фронту
MCUCSR=0x00;
GIFR=1<<INTF1;				//Сброс флага прерывания

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=1<<OCIE1A;			//Разрешение прерывания по совпадению A TC1

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// Global enable interrupts
#asm("sei")         //Разрешение прерываний

while (1)           //Бесконечный цикл
      {
      };
}
