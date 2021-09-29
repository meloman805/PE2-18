#include <mega16.h>
#include <delay.h>
//библиотека графики 10 десятичных цифр (знакогенератор)
//////////////////////////0////1////2////3////4////5////6////7////8////9///
flash char dig_dec[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void main(void)
{
// Port C initialization
//Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
PORTC=0x00;
DDRC=0xFF;

// Port B initialization
//Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=In Func1=In Func0=In
PORTB=0x00;
DDRB=0b00001000;

while(1)
      {
      unsigned char i;

        for (i=0;i<10;i++)
        {
        PORTC =  dig_dec[i];/*загрузка в PORTC кода графики очередной цифры
                            из массива знакогенератора dig_dec[i]*/
        PORTB = 0b00001000; //включение катодного ключа
        delay_ms(500);      //задержка 0,5 секунды

        PORTC =0x00;        //Гашение кратковременное (здесь необязательно)
        PORTB =0x00;
        delay_us(1);
        };

      };
}

