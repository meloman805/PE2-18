.include "m16def.inc"
.def temp=R16

.org 0

init: ldi temp,low(RAMEND)
      out SPL,temp
      ldi temp,high(RAMEND)
      out SPH,temp
      
      ldi temp,0b00000000
      out DDRD,temp
      ldi temp,0b00000001
      out PORTD,temp
      ldi temp,0b00000001
      out DDRC,temp
     
start: in temp,PIND
	 andi temp,0b00000001
	 cpi temp,0x00
	 breq led
	 
	 ldi temp,0x00
	 out PORTC,temp
	 jmp start
led:	ldi temp,0x01
	 out PORTC,temp
	 jmp start