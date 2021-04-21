.include "m16def.inc"
.def temp=R16 		
.def	temp1 = R17 	
.equ i=2
.org 0
init: 	ldi temp, low(RAMEND)
out SPL, temp 		
ldi temp, high(RAMEND)
out SPH, temp

L1:		       ldi temp, 0xFF
		       out DDRC, temp
		       ldi ZL, Low (ArraySin*2)
		       ldi ZH, High (ArraySin*2)
		       adiw ZL:ZH,i
		       lpm temp1,Z
		       out DDRC,temp1
		       rjmp L1
	
ArraySin:	   .db 128,153,177,199,217,234,245,253,255,253,245,234,218,199,177, 53,128, 103, 79, 57, 38, 22, 10, 3, 1, 3, 11, 22, 38, 57, 79, 103 
