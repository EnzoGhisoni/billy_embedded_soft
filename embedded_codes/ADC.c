/*
 * ADC.c
 *
 * Created: 11/12/2020 09:41:58
 *  Author: Enzo
 */ 
#include "ADC.h"

void initADC(void) {
	ADMUX |= (1 << REFS0) | (1 << MUX0); //reference voltage on AVCC, and use ADC1
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC clock prescaler / 8
	ADCSRA |= (1 << ADEN); //enables the ADC
}

uint16_t measurePotentiometerValue(){
	uint16_t potentiometerValue;
	ADCSRA |= (1 << ADSC); //start ADC conversion
	while((ADCSRA & (1 << ADSC))) //wait until ADSC bit is clear, i.e., ADC conversion is done
	{}
	//read ADC value in
	uint8_t theLowADC = ADCL;
	potentiometerValue = ADCH << 8 | theLowADC;
	//potentiometerValue = (potentiometerValue/1024)-1;
	return potentiometerValue;
}