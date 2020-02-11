;
; regulator.inc
;
;  Created: 2020-01-15
;  Author: Eric Grevillius
; 

;====================================================
; initialize the ADC and interrupt
;====================================================
regulator_init:
	CBI		DDRC,	0										; Set PC0 to input

	LDI		TEMP,	0b01000000								; Set reference voltage (internal 5V and select Single Ended Input for ADC0
	STS		ADMUX,	TEMP									; Store it to ADMUX	=	01000000
	
	LDI		TEMP,	0b00000001								; disable digital input on ADC0
	STS		DIDR0,	TEMP									; store it to DIDR0	=	00000001

	; The ADCSRB is already cleared by default 
	; and is therefore already in free running mode

	LDI		TEMP,	0xFF									; Reset any pending ADC interrupts, set prescaler 128, 
															;enable Auto Trigger, enable Interrupt, enable ADC and start conversion
	STS		ADCSRA, TEMP									; store it to ADCSRA =	11111111
	SEI														; Enable global interrupts
	RET

;====================================================
; Read value of the ADC
;====================================================
adc_interrupt:				
	; Read the result of the conversion
	LDS		ADC_RES,	ADCL	; Save the value of the ADCL to display later
	LDS		TEMP,		ADCH	; Trigger next conversion by reading from ADCH
	RETI