.include "m16def.inc"
.def	tempL = R16
.def	tempH = R17
.def 	temp = R18
.equ i = 6
.org 0
init: 	 	ldi temp,low(RAMEND)
		out SPL,temp
		ldi temp,high(RAMEND)
		out SPH,temp	 
L1:		       ldi temp, 0xFF
		       out DDRC, temp
		       out DDRD,temp
		       ldi ZL, Low (ArrayKub*2)
		       ldi ZH, High (ArrayKub*2)
		       adiw ZL:ZH,i*2
		       lpm tempH,Z+
		       lpm tempL,Z+
		       out DDRC,tempL
		       out DDRD,tempH
		       rjmp L1
.org 0x0080 
ArrayKub: .dw 0,1,8,27,64,216,343,512,729,1000,1331,1728,2197,2744,3375,4096,4913,5832,6859,8000,9261,10648,12167
