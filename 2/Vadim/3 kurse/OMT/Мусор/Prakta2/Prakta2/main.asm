.nolist
.include "m16def.inc"
.list
.def Temp=R16 ;���������� �������� R16 ����� Temp
.equ a=6
.equ b=7
.equ c=8
.equ d=9
.equ f=10
			.org 00
			RJMP start
			.org 0x2A

START:	
			
			ldi temp,a
			sts var,temp
			ldi temp,b
			sts var+1,temp
			ldi temp,c
			sts var+2,temp
			ldi temp,d
			sts var+3,temp
			ldi temp,f
			sts var+4,temp

			lds temp,0x0060
			sts var2,temp
			lds temp,0x0061
			sts var2+1,temp
			lds temp,0x0062
			sts var2+2,temp
			lds temp,0x0063
			sts var2+3,temp
			lds temp,0x0064
			sts var2+4,temp

L1:			RJMP L1
.DSEG ;��������� ��������� � ������ ������
	.org $60 ;��������� ���������� ������ ����������
	var: /*����� ���������� ������ DSEG ����������*/
	.BYTE 5 /*�������������� � DSEG 5-� ����������� �����*/
	.org $80
	var2:
	.byte 5