
#pragma used+
sfrb TWBR=0;
sfrb TWSR=1;
sfrb TWAR=2;
sfrb TWDR=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      
sfrb ADCSRA=6;
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRRL=9;
sfrb UCSRB=0xa;
sfrb UCSRA=0xb;
sfrb UDR=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb PINA=0x19;
sfrb DDRA=0x1a;
sfrb PORTA=0x1b;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   
sfrb UBRRH=0x20;
sfrb UCSRC=0X20;
sfrb WDTCR=0x21;
sfrb ASSR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb SFIOR=0x30;
sfrb OSCCAL=0x31;
sfrb OCDR=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TWCR=0x36;
sfrb SPMCR=0x37;
sfrb TIFR=0x38;
sfrb TIMSK=0x39;
sfrb GIFR=0x3a;
sfrb GICR=0x3b;
sfrb OCR0=0X3c;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x40
	.EQU __sm_mask=0xB0
	.EQU __sm_powerdown=0x20
	.EQU __sm_powersave=0x30
	.EQU __sm_standby=0xA0
	.EQU __sm_ext_standby=0xB0
	.EQU __sm_adc_noise_red=0x10
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

#pragma used+

unsigned char bcd2bin(unsigned char n);
unsigned char bin2bcd(unsigned char n);

#pragma used-

#pragma library bcd.lib

flash unsigned char  DIG_DEC[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

unsigned char BCD_UNPACKED[4]={0,0,0,0};    

unsigned char i=0;                           

interrupt [3] void ext_int1_isr(void)
{
if (MCUCR==0x0C)    {
MCUCR=0x08;     
TCCR0=0x02;     
}
else                {

unsigned char sot=0, bin_time;
TCCR0=0x00;     
bin_time=TCNT0; 
PORTA=TCNT0;    
TCNT0=0x00;     
MCUCR=0x0C;     

sot=0;
while (bin_time>=100)   
{
bin_time-=100; sot++;
};                          
sot=bin2bcd(sot);               
bin_time=bin2bcd(bin_time);     
BCD_UNPACKED[0]=sot>>4;         
BCD_UNPACKED[1]=sot&0x0F;       
BCD_UNPACKED[2]=bin_time>>4;    
BCD_UNPACKED[3]=bin_time&0x0F;  
};
}

interrupt [7] void timer1_compa_isr(void)
{                   
PORTB=0x00;         
PORTC=0x00;         

PORTB=0b1000>>i;                    
PORTC=DIG_DEC[BCD_UNPACKED[i]];     
i++;                
if (i>3) i=0;       
}

void main(void)
{

PORTA=0x00;
DDRA=0xFF;                          

PORTB=0x00;
DDRB=0x0F;                          

PORTC=0x00;
DDRC=0xFF;                          

TCCR0=0x00;                         
TCNT0=0x00;
OCR0=0x00;

TCCR1A=0x00;
TCCR1B=0x09;        
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x4E;        
OCR1AL=0x20;        
OCR1BH=0x00;
OCR1BL=0x00;

TIMSK=0x10;

GICR|=0x80;                         
MCUCR=0x0C;                         
MCUCSR=0x00;
GIFR=0x80;

#asm("sei")

while (1)                               
{                                 

};
}
