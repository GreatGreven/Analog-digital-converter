;
; Analog-digital-converter.asm
;
; Created: 2020-01-15
; Author : Eric Grevillius
;

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			RESET		 =	0x0000			; reset vector
	.EQU			ADC_VECTOR	 =	0x002A			; Analog-to-digital-conversion vector
	.EQU			PM_START	 =	0x0072			; start of program
	.DEF			TEMP		 = R16
	.DEF			ADC_RES		 = R17
	.DEF			DELAY_INPUT	 = R24


;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG			RESET
	RJMP			init

	.ORG			ADC_VECTOR
	RJMP			adc_interrupt

	.ORG			PM_START
	.INCLUDE		"delay.inc"
	.INCLUDE		"regulator.inc"

	
;==============================================================================
; Basic initializations of stack pointer, etc.
;==============================================================================
init:
	LDI				TEMP,			LOW(RAMEND)		; Set stack pointer
	OUT				SPL,			TEMP			; at the end of RAM.
	LDI				TEMP,			HIGH(RAMEND)
	OUT				SPH,			TEMP
	RCALL			init_pins						; Initialize pins
	RCALL			regulator_init					; Initialize regulator
	LDI				TEMP,			0
	LDI				ADC_RES,		0
	RJMP			main							; Jump to main

;==============================================================================
; Initialise I/O pins
;==============================================================================
init_pins:

	SBI		DDRB,	5		; set on-board LED to output
	LDI		TEMP,	0xFF
	OUT		DDRD,	TEMP	; set all pins on PORTD to output
	RET

main:
	OUT		PORTD,		ADC_RES
	RJMP	main
