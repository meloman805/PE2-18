/*****************************************************
Project : ADC
Version :
Date    : 15.10.2014
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
/*Здесь запуск АЦП на преобразование - по прерыванию INT0, а считывание данных с АЦП -
по опросу готовности (поллингу), все это делается внутри обработчика INT0*/
#include <mega16.h>
#include <delay.h>

#define ADC_VREF_TYPE 0x00 //определен код выбора внешнего опорного источника

/* Read the AD conversion result: функция считывания
результата аналого-цифрового преобразования */
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);//Установка выбранного опорного источника и канала АЦП
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
//ADCSRA|=1<<ADSC;	//Запуск АЦП на преобр. – здесь не нужен (уже запущен)
// Wait for the AD conversion to complete
while ((ADCSRA & 1<<ADIF)==0);          /*ожидаем окончания преобразования
                                        (пока не установился флаг прерывания АЦП ADIF)*/
ADCSRA|=1<<ADIF;                        //сбрасываем флаг готовности и считываем данные
return ADCW; //возвращаемая  величина - содержимое регистра данных АЦП
}

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{               //АЦП по этому прерыванию уже запустился на преобразование
read_adc(0);    /*Считывание результата преобразования за счет
                обращения к функции преобразования сигнала, подаваемого на вход AIN0*/
PORTB=ADCL;
PORTC=ADCH;
}

void main(void)
{
// Port B initialization
PORTB=0x00;     //Порт B - на вывод данных
DDRB=0xff;      //для вывода младшего байта преобразованных АЦП данных

// Port C initialization
PORTC=0x00;     //Порт С - на вывод данных
DDRC=0xff;      //для вывода старшего байта преобразованных АЦП данных

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: Off
// INT2: Off
GICR|=1<<INT0;  //Разрешение прерывания INT0
MCUCR=1<<ISC01; //Запуск прерывания - по заднему фронту INT0
MCUCSR=0x00;
GIFR=1<<INTF0;

// ADC initialization
// ADC Clock frequency: 250,000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: External IRQ0
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0xA5;    //частота 250 кГц, запуск в соотв. с уст. разрядов 7-5 SFIOR
SFIOR&=0x1F;
SFIOR|=0x40;    //Запуск по внешнему прерыванию INT0

// Global enable interrupts
#asm("sei")

while (1)       //бесконечный цикл, выход из которого  происходит
      {         //по прерываннию INT0
      // Place your code here
      };
}
