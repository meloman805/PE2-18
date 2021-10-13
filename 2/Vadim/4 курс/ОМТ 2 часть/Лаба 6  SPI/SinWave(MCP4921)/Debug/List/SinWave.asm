
;CodeVisionAVR C Compiler V3.12 Advanced
;(C) Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Build configuration    : Debug
;Chip type              : ATmega328P
;Program type           : Application
;Clock frequency        : 16,000000 MHz
;Memory model           : Small
;Optimize for           : Size
;(s)printf features     : int, width
;(s)scanf features      : int, width
;External RAM size      : 0
;Data Stack size        : 512 byte(s)
;Heap size              : 0 byte(s)
;Promote 'char' to 'int': Yes
;'char' is unsigned     : Yes
;8 bit enums            : Yes
;Global 'const' stored in FLASH: Yes
;Enhanced function parameter passing: Yes
;Enhanced core instructions: On
;Automatic register allocation for global variables: On
;Smart register allocation: On

	#define _MODEL_SMALL_

	#pragma AVRPART ADMIN PART_NAME ATmega328P
	#pragma AVRPART MEMORY PROG_FLASH 32768
	#pragma AVRPART MEMORY EEPROM 1024
	#pragma AVRPART MEMORY INT_SRAM SIZE 2048
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU EECR=0x1F
	.EQU EEDR=0x20
	.EQU EEARL=0x21
	.EQU EEARH=0x22
	.EQU SPSR=0x2D
	.EQU SPDR=0x2E
	.EQU SMCR=0x33
	.EQU MCUSR=0x34
	.EQU MCUCR=0x35
	.EQU WDTCSR=0x60
	.EQU UCSR0A=0xC0
	.EQU UDR0=0xC6
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU GPIOR0=0x1E

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0100
	.EQU __SRAM_END=0x08FF
	.EQU __DSTACK_SIZE=0x0200
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTW2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD2FN
	LDI  R26,LOW(2*@0+(@1))
	LDI  R27,HIGH(2*@0+(@1))
	LDI  R24,BYTE3(2*@0+(@1))
	LDI  R25,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	PUSH R26
	PUSH R27
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	POP  R27
	POP  R26
	ICALL
	.ENDM

	.MACRO __CALL2EX
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	CALL __EEPROMRDD
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1STACK
	IN   R30,SPL
	IN   R31,SPH
	ADIW R30,@0+1
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z
	MOVW R30,R0
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;GPIOR0 INITIALIZATION VALUE
	.EQU __GPIOR0_INIT=0x00

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_samples:
	.DB  0x0,0x8,0x19,0x8,0x32,0x8,0x4B,0x8
	.DB  0x64,0x8,0x7E,0x8,0x97,0x8,0xB0,0x8
	.DB  0xC9,0x8,0xE2,0x8,0xFB,0x8,0x14,0x9
	.DB  0x2D,0x9,0x45,0x9,0x5E,0x9,0x77,0x9
	.DB  0x90,0x9,0xA8,0x9,0xC1,0x9,0xD9,0x9
	.DB  0xF2,0x9,0xA,0xA,0x22,0xA,0x3A,0xA
	.DB  0x53,0xA,0x6B,0xA,0x82,0xA,0x9A,0xA
	.DB  0xB2,0xA,0xCA,0xA,0xE1,0xA,0xF8,0xA
	.DB  0x10,0xB,0x27,0xB,0x3E,0xB,0x55,0xB
	.DB  0x6C,0xB,0x82,0xB,0x99,0xB,0xAF,0xB
	.DB  0xC5,0xB,0xDC,0xB,0xF1,0xB,0x7,0xC
	.DB  0x1D,0xC,0x32,0xC,0x48,0xC,0x5D,0xC
	.DB  0x72,0xC,0x87,0xC,0x9B,0xC,0xB0,0xC
	.DB  0xC4,0xC,0xD8,0xC,0xEC,0xC,0x0,0xD
	.DB  0x13,0xD,0x27,0xD,0x3A,0xD,0x4D,0xD
	.DB  0x5F,0xD,0x72,0xD,0x84,0xD,0x96,0xD
	.DB  0xA8,0xD,0xBA,0xD,0xCB,0xD,0xDC,0xD
	.DB  0xED,0xD,0xFE,0xD,0xF,0xE,0x1F,0xE
	.DB  0x2F,0xE,0x3F,0xE,0x4F,0xE,0x5E,0xE
	.DB  0x6D,0xE,0x7C,0xE,0x8A,0xE,0x99,0xE
	.DB  0xA7,0xE,0xB5,0xE,0xC2,0xE,0xD0,0xE
	.DB  0xDD,0xE,0xE9,0xE,0xF6,0xE,0x2,0xF
	.DB  0xE,0xF,0x1A,0xF,0x25,0xF,0x30,0xF
	.DB  0x3B,0xF,0x46,0xF,0x50,0xF,0x5A,0xF
	.DB  0x64,0xF,0x6E,0xF,0x77,0xF,0x80,0xF
	.DB  0x88,0xF,0x91,0xF,0x99,0xF,0xA0,0xF
	.DB  0xA8,0xF,0xAF,0xF,0xB6,0xF,0xBC,0xF
	.DB  0xC3,0xF,0xC9,0xF,0xCE,0xF,0xD4,0xF
	.DB  0xD9,0xF,0xDD,0xF,0xE2,0xF,0xE6,0xF
	.DB  0xEA,0xF,0xED,0xF,0xF1,0xF,0xF4,0xF
	.DB  0xF6,0xF,0xF8,0xF,0xFA,0xF,0xFC,0xF
	.DB  0xFE,0xF,0xFF,0xF,0xFF,0xF,0xFF,0xF
	.DB  0xFF,0xF,0xFF,0xF,0xFF,0xF,0xFF,0xF
	.DB  0xFE,0xF,0xFC,0xF,0xFA,0xF,0xF8,0xF
	.DB  0xF6,0xF,0xF4,0xF,0xF1,0xF,0xED,0xF
	.DB  0xEA,0xF,0xE6,0xF,0xE2,0xF,0xDD,0xF
	.DB  0xD9,0xF,0xD4,0xF,0xCE,0xF,0xC9,0xF
	.DB  0xC3,0xF,0xBC,0xF,0xB6,0xF,0xAF,0xF
	.DB  0xA8,0xF,0xA0,0xF,0x99,0xF,0x91,0xF
	.DB  0x88,0xF,0x80,0xF,0x77,0xF,0x6E,0xF
	.DB  0x64,0xF,0x5A,0xF,0x50,0xF,0x46,0xF
	.DB  0x3B,0xF,0x30,0xF,0x25,0xF,0x1A,0xF
	.DB  0xE,0xF,0x2,0xF,0xF6,0xE,0xE9,0xE
	.DB  0xDD,0xE,0xD0,0xE,0xC2,0xE,0xB5,0xE
	.DB  0xA7,0xE,0x99,0xE,0x8A,0xE,0x7C,0xE
	.DB  0x6D,0xE,0x5E,0xE,0x4F,0xE,0x3F,0xE
	.DB  0x2F,0xE,0x1F,0xE,0xF,0xE,0xFE,0xD
	.DB  0xED,0xD,0xDC,0xD,0xCB,0xD,0xBA,0xD
	.DB  0xA8,0xD,0x96,0xD,0x84,0xD,0x72,0xD
	.DB  0x5F,0xD,0x4D,0xD,0x3A,0xD,0x27,0xD
	.DB  0x13,0xD,0x0,0xD,0xEC,0xC,0xD8,0xC
	.DB  0xC4,0xC,0xB0,0xC,0x9B,0xC,0x87,0xC
	.DB  0x72,0xC,0x5D,0xC,0x48,0xC,0x32,0xC
	.DB  0x1D,0xC,0x7,0xC,0xF1,0xB,0xDC,0xB
	.DB  0xC5,0xB,0xAF,0xB,0x99,0xB,0x82,0xB
	.DB  0x6C,0xB,0x55,0xB,0x3E,0xB,0x27,0xB
	.DB  0x10,0xB,0xF8,0xA,0xE1,0xA,0xCA,0xA
	.DB  0xB2,0xA,0x9A,0xA,0x82,0xA,0x6B,0xA
	.DB  0x53,0xA,0x3A,0xA,0x22,0xA,0xA,0xA
	.DB  0xF2,0x9,0xD9,0x9,0xC1,0x9,0xA8,0x9
	.DB  0x90,0x9,0x77,0x9,0x5E,0x9,0x45,0x9
	.DB  0x2D,0x9,0x14,0x9,0xFB,0x8,0xE2,0x8
	.DB  0xC9,0x8,0xB0,0x8,0x97,0x8,0x7E,0x8
	.DB  0x64,0x8,0x4B,0x8,0x32,0x8,0x19,0x8
	.DB  0x0,0x8,0xE7,0x7,0xCE,0x7,0xB5,0x7
	.DB  0x9C,0x7,0x82,0x7,0x69,0x7,0x50,0x7
	.DB  0x37,0x7,0x1E,0x7,0x5,0x7,0xEC,0x6
	.DB  0xD3,0x6,0xBB,0x6,0xA2,0x6,0x89,0x6
	.DB  0x70,0x6,0x58,0x6,0x3F,0x6,0x27,0x6
	.DB  0xE,0x6,0xF6,0x5,0xDE,0x5,0xC6,0x5
	.DB  0xAD,0x5,0x95,0x5,0x7E,0x5,0x66,0x5
	.DB  0x4E,0x5,0x36,0x5,0x1F,0x5,0x8,0x5
	.DB  0xF0,0x4,0xD9,0x4,0xC2,0x4,0xAB,0x4
	.DB  0x94,0x4,0x7E,0x4,0x67,0x4,0x51,0x4
	.DB  0x3B,0x4,0x24,0x4,0xF,0x4,0xF9,0x3
	.DB  0xE3,0x3,0xCE,0x3,0xB8,0x3,0xA3,0x3
	.DB  0x8E,0x3,0x79,0x3,0x65,0x3,0x50,0x3
	.DB  0x3C,0x3,0x28,0x3,0x14,0x3,0x0,0x3
	.DB  0xED,0x2,0xD9,0x2,0xC6,0x2,0xB3,0x2
	.DB  0xA1,0x2,0x8E,0x2,0x7C,0x2,0x6A,0x2
	.DB  0x58,0x2,0x46,0x2,0x35,0x2,0x24,0x2
	.DB  0x13,0x2,0x2,0x2,0xF1,0x1,0xE1,0x1
	.DB  0xD1,0x1,0xC1,0x1,0xB1,0x1,0xA2,0x1
	.DB  0x93,0x1,0x84,0x1,0x76,0x1,0x67,0x1
	.DB  0x59,0x1,0x4B,0x1,0x3E,0x1,0x30,0x1
	.DB  0x23,0x1,0x17,0x1,0xA,0x1,0xFE,0x0
	.DB  0xF2,0x0,0xE6,0x0,0xDB,0x0,0xD0,0x0
	.DB  0xC5,0x0,0xBA,0x0,0xB0,0x0,0xA6,0x0
	.DB  0x9C,0x0,0x92,0x0,0x89,0x0,0x80,0x0
	.DB  0x78,0x0,0x6F,0x0,0x67,0x0,0x60,0x0
	.DB  0x58,0x0,0x51,0x0,0x4A,0x0,0x44,0x0
	.DB  0x3D,0x0,0x37,0x0,0x32,0x0,0x2C,0x0
	.DB  0x27,0x0,0x23,0x0,0x1E,0x0,0x1A,0x0
	.DB  0x16,0x0,0x13,0x0,0xF,0x0,0xC,0x0
	.DB  0xA,0x0,0x8,0x0,0x6,0x0,0x4,0x0
	.DB  0x2,0x0,0x1,0x0,0x1,0x0,0x0,0x0
	.DB  0x0,0x0,0x0,0x0,0x1,0x0,0x1,0x0
	.DB  0x2,0x0,0x4,0x0,0x6,0x0,0x8,0x0
	.DB  0xA,0x0,0xC,0x0,0xF,0x0,0x13,0x0
	.DB  0x16,0x0,0x1A,0x0,0x1E,0x0,0x23,0x0
	.DB  0x27,0x0,0x2C,0x0,0x32,0x0,0x37,0x0
	.DB  0x3D,0x0,0x44,0x0,0x4A,0x0,0x51,0x0
	.DB  0x58,0x0,0x60,0x0,0x67,0x0,0x6F,0x0
	.DB  0x78,0x0,0x80,0x0,0x89,0x0,0x92,0x0
	.DB  0x9C,0x0,0xA6,0x0,0xB0,0x0,0xBA,0x0
	.DB  0xC5,0x0,0xD0,0x0,0xDB,0x0,0xE6,0x0
	.DB  0xF2,0x0,0xFE,0x0,0xA,0x1,0x17,0x1
	.DB  0x23,0x1,0x30,0x1,0x3E,0x1,0x4B,0x1
	.DB  0x59,0x1,0x67,0x1,0x76,0x1,0x84,0x1
	.DB  0x93,0x1,0xA2,0x1,0xB1,0x1,0xC1,0x1
	.DB  0xD1,0x1,0xE1,0x1,0xF1,0x1,0x2,0x2
	.DB  0x13,0x2,0x24,0x2,0x35,0x2,0x46,0x2
	.DB  0x58,0x2,0x6A,0x2,0x7C,0x2,0x8E,0x2
	.DB  0xA1,0x2,0xB3,0x2,0xC6,0x2,0xD9,0x2
	.DB  0xED,0x2,0x0,0x3,0x14,0x3,0x28,0x3
	.DB  0x3C,0x3,0x50,0x3,0x65,0x3,0x79,0x3
	.DB  0x8E,0x3,0xA3,0x3,0xB8,0x3,0xCE,0x3
	.DB  0xE3,0x3,0xF9,0x3,0xF,0x4,0x24,0x4
	.DB  0x3B,0x4,0x51,0x4,0x67,0x4,0x7E,0x4
	.DB  0x94,0x4,0xAB,0x4,0xC2,0x4,0xD9,0x4
	.DB  0xF0,0x4,0x8,0x5,0x1F,0x5,0x36,0x5
	.DB  0x4E,0x5,0x66,0x5,0x7E,0x5,0x95,0x5
	.DB  0xAD,0x5,0xC6,0x5,0xDE,0x5,0xF6,0x5
	.DB  0xE,0x6,0x27,0x6,0x3F,0x6,0x58,0x6
	.DB  0x70,0x6,0x89,0x6,0xA2,0x6,0xBB,0x6
	.DB  0xD3,0x6,0xEC,0x6,0x5,0x7,0x1E,0x7
	.DB  0x37,0x7,0x50,0x7,0x69,0x7,0x82,0x7
	.DB  0x9C,0x7,0xB5,0x7,0xCE,0x7,0xE7,0x7

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GPIOR0 INITIALIZATION
	LDI  R30,__GPIOR0_INIT
	OUT  GPIOR0,R30

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x300

	.CSEG
;/*******************************************************
;Chip type               : ATmega328P
;AVR Core Clock frequency: 16,000000 MHz
;*******************************************************/
;#include <mega328p.h>
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_adc_noise_red=0x02
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.SET power_ctrl_reg=smcr
	#endif
;#include <delay.h>
;
;// Declare your global variables here
;flash unsigned int samples[512]=              //таблица синуса с 512 отсчетами
;{
;  2048, 2073, 2098, 2123, 2148, 2174, 2199, 2224,
;  2249, 2274, 2299, 2324, 2349, 2373, 2398, 2423,
;  2448, 2472, 2497, 2521, 2546, 2570, 2594, 2618,
;  2643, 2667, 2690, 2714, 2738, 2762, 2785, 2808,
;  2832, 2855, 2878, 2901, 2924, 2946, 2969, 2991,
;  3013, 3036, 3057, 3079, 3101, 3122, 3144, 3165,
;  3186, 3207, 3227, 3248, 3268, 3288, 3308, 3328,
;  3347, 3367, 3386, 3405, 3423, 3442, 3460, 3478,
;  3496, 3514, 3531, 3548, 3565, 3582, 3599, 3615,
;  3631, 3647, 3663, 3678, 3693, 3708, 3722, 3737,
;  3751, 3765, 3778, 3792, 3805, 3817, 3830, 3842,
;  3854, 3866, 3877, 3888, 3899, 3910, 3920, 3930,
;  3940, 3950, 3959, 3968, 3976, 3985, 3993, 4000,
;  4008, 4015, 4022, 4028, 4035, 4041, 4046, 4052,
;  4057, 4061, 4066, 4070, 4074, 4077, 4081, 4084,
;  4086, 4088, 4090, 4092, 4094, 4095, 4095, 4095,
;  4095, 4095, 4095, 4095, 4094, 4092, 4090, 4088,
;  4086, 4084, 4081, 4077, 4074, 4070, 4066, 4061,
;  4057, 4052, 4046, 4041, 4035, 4028, 4022, 4015,
;  4008, 4000, 3993, 3985, 3976, 3968, 3959, 3950,
;  3940, 3930, 3920, 3910, 3899, 3888, 3877, 3866,
;  3854, 3842, 3830, 3817, 3805, 3792, 3778, 3765,
;  3751, 3737, 3722, 3708, 3693, 3678, 3663, 3647,
;  3631, 3615, 3599, 3582, 3565, 3548, 3531, 3514,
;  3496, 3478, 3460, 3442, 3423, 3405, 3386, 3367,
;  3347, 3328, 3308, 3288, 3268, 3248, 3227, 3207,
;  3186, 3165, 3144, 3122, 3101, 3079, 3057, 3036,
;  3013, 2991, 2969, 2946, 2924, 2901, 2878, 2855,
;  2832, 2808, 2785, 2762, 2738, 2714, 2690, 2667,
;  2643, 2618, 2594, 2570, 2546, 2521, 2497, 2472,
;  2448, 2423, 2398, 2373, 2349, 2324, 2299, 2274,
;  2249, 2224, 2199, 2174, 2148, 2123, 2098, 2073,
;  2048, 2023, 1998, 1973, 1948, 1922, 1897, 1872,
;  1847, 1822, 1797, 1772, 1747, 1723, 1698, 1673,
;  1648, 1624, 1599, 1575, 1550, 1526, 1502, 1478,
;  1453, 1429, 1406, 1382, 1358, 1334, 1311, 1288,
;  1264, 1241, 1218, 1195, 1172, 1150, 1127, 1105,
;  1083, 1060, 1039, 1017,  995,  974,  952,  931,
;   910,  889,  869,  848,  828,  808,  788,  768,
;   749,  729,  710,  691,  673,  654,  636,  618,
;   600,  582,  565,  548,  531,  514,  497,  481,
;   465,  449,  433,  418,  403,  388,  374,  359,
;   345,  331,  318,  304,  291,  279,  266,  254,
;   242,  230,  219,  208,  197,  186,  176,  166,
;   156,  146,  137,  128,  120,  111,  103,   96,
;    88,   81,   74,   68,   61,   55,   50,   44,
;    39,   35,   30,   26,   22,   19,   15,   12,
;    10,    8,    6,    4,    2,    1,    1,    0,
;     0,    0,    1,    1,    2,    4,    6,    8,
;    10,   12,   15,   19,   22,   26,   30,   35,
;    39,   44,   50,   55,   61,   68,   74,   81,
;    88,   96,  103,  111,  120,  128,  137,  146,
;   156,  166,  176,  186,  197,  208,  219,  230,
;   242,  254,  266,  279,  291,  304,  318,  331,
;   345,  359,  374,  388,  403,  418,  433,  449,
;   465,  481,  497,  514,  531,  548,  565,  582,
;   600,  618,  636,  654,  673,  691,  710,  729,
;   749,  768,  788,  808,  828,  848,  869,  889,
;   910,  931,  952,  974,  995, 1017, 1039, 1060,
;  1083, 1105, 1127, 1150, 1172, 1195, 1218, 1241,
;  1264, 1288, 1311, 1334, 1358, 1382, 1406, 1429,
;  1453, 1478, 1502, 1526, 1550, 1575, 1599, 1624,
;  1648, 1673, 1698, 1723, 1747, 1772, 1797, 1822,
;  1847, 1872, 1897, 1922, 1948, 1973, 1998, 2023
;};
;
;//flash unsigned int samples[32] =                    //таблица синуса с 32 отсчётами
;//{
;//  2048, 2447, 2831, 3185, 3495, 3750, 3939, 4056,
;//  4095, 4056, 3939, 3750, 3495, 3185, 2831, 2447,
;//  2048, 1648, 1264,  910,  600,  345,  156,   39,
;//     0,   39,  156,  345,  600,  910, 1264, 1648
;//};
;// SPI functions
;//#include <spi.h>
;//Определение линий портов для SPI МК Atmega328p
;#define SS PORTB2
;#define SCK PORTB5
;#define MOSI PORTB3
;//Определение разрядов старшего байта передаваемого в ЦАП слова
;#define AB 7    // Для MCP4921 должен быть 0
;#define BUF 6   // 1 - есть буферизация Vref, 0 - нет буферизации Vref
;#define GA 5    // 1 - GAIN=1, 0 - GAIN=0
;#define SHDN 4  // 1 - выходы ЦАП включены, 0 - выходы в высокоимпедансном состоянии
;
;/*ФУНКЦИЯ ПЕРЕДАЧИ БАЙТА ПО SPI-ИНТЕРФЕЙСУ ОТ MASTER-устройства(МК)*/
;void SPI_MasterTransmit(char d) //в переменную d принимаем байт для отправки по SPI интерфейсу
; 0000 0062   {

	.CSEG
_SPI_MasterTransmit:
; .FSTART _SPI_MasterTransmit
; 0000 0063   SPDR = d;                     //передаем байт в сдвиговый регистр SPDR
	ST   -Y,R26
;	d -> Y+0
	LD   R30,Y
	OUT  0x2E,R30
; 0000 0064   while(~SPSR & (1<<SPIF));     //ждем пока появится 1 в разряде SPIF (7) регистра
_0x3:
	IN   R30,0x2D
	COM  R30
	ANDI R30,LOW(0x80)
	BRNE _0x3
; 0000 0065                                 //SPSR - признак завершения передачи байта
; 0000 0066   }                             //байт передан устройству Slave, возврат
	ADIW R28,1
	RET
; .FEND
;
;/*ФУНКЦИЯ ОТПРАВКИ 16 БИТ ДАННЫХ ПО SPI-ИНТЕРФЕЙСУ - установки напряжения на выходе ЦАП*/
;void SET_Voltage(unsigned int cd)
; 0000 006A {
_SET_Voltage:
; .FSTART _SET_Voltage
; 0000 006B PORTB&=~(1<<SS);    //на /SS установить 0 для выбора ведомого устройства (ЦАП)
	ST   -Y,R27
	ST   -Y,R26
;	cd -> Y+0
	CBI  0x5,2
; 0000 006C 
; 0000 006D //Отправляем по SPI (0x1DDD) первые 4 бита(15-12) конфигурационные,
; 0000 006E //остальные данные(11-0) - код для напряжения, которое будет установлено на выходе ЦАП
; 0000 006F 
; 0000 0070 //Выводим ЦАП из режима SHDN (SHDN=1), устанавливаем Gain=1
; 0000 0071 //поскольку переменная cd 16 битная, сдвигаем старшие 8 бит вправо(первыми отправляем старшие 8 бит).
; 0000 0072 SPI_MasterTransmit((0<<AB)|(0<<BUF)|(1<<GA)|(1<<SHDN)|(cd>>8)); //отправляем старшие(15-8) 8 бит данных:
	LDD  R30,Y+1
	ANDI R31,HIGH(0x0)
	ORI  R30,LOW(0x30)
	MOV  R26,R30
	RCALL _SPI_MasterTransmit
; 0000 0073 //4 конфигурационных бита (биты 7-4) и старшую тетраду данных (биты 3-0)
; 0000 0074 
; 0000 0075 SPI_MasterTransmit(cd);         //Отправляем по SPI младшие(0-7) 8 бит данных
	LD   R26,Y
	RCALL _SPI_MasterTransmit
; 0000 0076 PORTB|=(1<<SS);                 //на /SS установить 1, т.е. отключить ведомое устройство
	SBI  0x5,2
; 0000 0077 }
	ADIW R28,2
	RET
; .FEND
;
;/*ГЛАВНАЯ ФУНКЦИЯ*/
;void main(void)
; 0000 007B {
_main:
; .FSTART _main
; 0000 007C unsigned int i, step=4;
; 0000 007D // Crystal Oscillator division factor: 1
; 0000 007E #pragma optsize-
; 0000 007F CLKPR=(1<<CLKPCE);
;	i -> R16,R17
;	step -> R18,R19
	__GETWRN 18,19,4
	LDI  R30,LOW(128)
	STS  97,R30
; 0000 0080 CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
	LDI  R30,LOW(0)
	STS  97,R30
; 0000 0081 #ifdef _OPTIMIZE_SIZE_
; 0000 0082 #pragma optsize+
; 0000 0083 #endif
; 0000 0084 
; 0000 0085 /*НАСТРОЙКА ПЕРИФЕРИИ*/
; 0000 0086 // Input/Output Ports initialization
; 0000 0087 // Port B initialization
; 0000 0088 // Function: Bit7=In Bit6=In Bit5=Out Bit4=In Bit3=Out Bit2=Out Bit1=In Bit0=In
; 0000 0089 // Выходные линии инт. SPI:   PB5-SCK;               PB3-MOSI;    PB2-/SS
; 0000 008A DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (1<<DDB3) | (1<<DDB2) | (0<<DDB1) | (0<<DDB0);
	LDI  R30,LOW(44)
	OUT  0x4,R30
; 0000 008B // State: Bit7=T Bit6=T Bit5=0 Bit4=T Bit3=0 Bit2=0 Bit1=T Bit0=T
; 0000 008C PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
	LDI  R30,LOW(0)
	OUT  0x5,R30
; 0000 008D 
; 0000 008E // SPI initialization
; 0000 008F // SPI Type: Master
; 0000 0090 // SPI Clock Rate: 2*4000,000 kHz - максимально возможная скорость передачи по SPI для данного МК
; 0000 0091 // SPI Clock Phase: Cycle Start
; 0000 0092 // SPI Clock Polarity: Low
; 0000 0093 // SPI Data Order: MSB First
; 0000 0094 SPCR=(0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
	LDI  R30,LOW(80)
	OUT  0x2C,R30
; 0000 0095 SPSR=(1<<SPI2X);
	LDI  R30,LOW(1)
	OUT  0x2D,R30
; 0000 0096 
; 0000 0097 while (1)
_0x6:
; 0000 0098       {
; 0000 0099       // Place your code here
; 0000 009A       //ЦИКЛИЧЕСКИЙ ВЫВОД ЗНАЧЕНИЙ МАССИВА СИНУСОВ В ЦАП
; 0000 009B       for (i=0;i<512;i=i+step)
	__GETWRN 16,17,0
_0xA:
	__CPWRN 16,17,512
	BRSH _0xB
; 0000 009C             {
; 0000 009D              SET_Voltage(samples[i]);
	MOVW R30,R16
	LDI  R26,LOW(_samples*2)
	LDI  R27,HIGH(_samples*2)
	LSL  R30
	ROL  R31
	ADD  R30,R26
	ADC  R31,R27
	CALL __GETW2PF
	RCALL _SET_Voltage
; 0000 009E             };
	__ADDWRR 16,17,18,19
	RJMP _0xA
_0xB:
; 0000 009F 
; 0000 00A0       }
	RJMP _0x6
; 0000 00A1 }
_0xC:
	RJMP _0xC
; .FEND

	.CSEG

	.CSEG
__GETW2PF:
	LPM  R26,Z+
	LPM  R27,Z
	RET

;END OF CODE MARKER
__END_OF_CODE:
