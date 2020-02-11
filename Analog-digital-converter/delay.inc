;
; delay.inc
;
; Author:	Eric Grevillius
;  Created: 2020-01-15
; 

;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
delay_1_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X µs
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R24				Input parameter data (X µs)
;==============================================================================
delay_micros:						;4
	NOP								;5
	NOP								;6
	NOP								;7
	NOP								;8
	CPI			R24,		0		;5
	BREQ		end_micros			;6/7									
	DEC			R24					;7c
	NOP								;				
	NOP								;
	NOP								;
	NOP								;
	NOP								;12c
	RCALL		delay_micros		;
									
end_micros:			
	NOP								;8c
	RET								;12c

;==============================================================================
; Delay of 1 ms
;	
; Uses registers:
;	R24		Input parameter data for 'delay_micros'
;==============================================================================
delay_1_ms:						
	LDI			R24,		0xFA
	RCALL		delay_micros
	LDI			R24,		0xFA
	RCALL		delay_micros
	LDI			R24,		0xFA
	RCALL		delay_micros
	LDI			R24,		0xEF
	RCALL		delay_micros
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R18				Copy of parameter data (X ms)
;	R24				Input parameter data (X ms)
;==============================================================================
delay_ms:
	MOV			R18,		R24
next_ms:
	CPI			R18,		0
	BREQ		end_ms
	RCALL		delay_1_ms
	DEC			R18
	RJMP		next_ms
end_ms:
	RET

;==============================================================================
; Delay of 1 s
;	
; Uses registers:
;	R24		Input parameter data for 'delay_ms'
;==============================================================================
delay_1_s:						
	LDI			R24,		0xFA
	RCALL		delay_ms
	LDI			R24,		0xFA
	RCALL		delay_ms
	LDI			R24,		0xFA
	RCALL		delay_ms
	LDI			R24,		0xFA
	RCALL		delay_ms
	RET

;==============================================================================
; Delay of X s
;	
; Uses registers:
;	R19				Copy of parameter data (X s)
;	R24				Input parameter data (X s)
;==============================================================================
delay_s:						
	MOV			R19,		R24
next_s:
	CPI			R19,		0
	BREQ		end_s
	RCALL		delay_1_s
	DEC			R19
	RJMP		next_s
end_s:
	RET