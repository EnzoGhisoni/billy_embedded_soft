/*
 * PWM.c
 *
 * Created: 05/12/2020 16:18:53
 *  Author: Enzo
 */ 
#include "PWM.h"

void configPWM(){
	/*
	Initialize the PWM for the motors control on the Timer 0
	*/
	
	// In our case, we want a pwm at 61.04Hz
	// Fcpu = 16MHz and Fpwm = Fcpu/(256*N)
	//	=> 61.035 = Fcpu/(256*N)
	// <=> N = 1024
	//set OCR0A PWM, fast PWM, prescaler = 1024, non-inverted
	TCCR0B = 0x05;
	TCCR0A = 0x83; // equal to 131 <=> 0b10000011
	// Computation of the PWM in non-inverting mode //timer0 pin5
	//OCR0A = (int) (dutyCycle * 256)/100 - 1;
	
	/*
	Initialize the PWM for the servomotor control on the Timer 1
	*/
	// Clear Timer/Counter Control Registers
	DDRB |= (1 << DDB2);
	// Clear Timer/Counter Control Registers
	TCCR1A = 0;
	TCCR1B = 0;

	// Set non-inverting mode
	//TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);
	// Set fast PWM Mode 14 (Fast PWM 8 bits)
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	// Set prescaler to 64 and starts PWM
	TCCR1B |= (1 << CS11);

	// Set PWM duty cycle
	ICR1 = 40000;
}

/**********************************************************************************************************
	This function sets the registers to have a fast PWM non-inveted with a prescaler of 1024 perfomed
	by the Timer0
	It takes are argument the duty cycle in %
**********************************************************************************************************/
void configPWM_Duty(float dutyCycle){
	// In our case, we want a pwm at 61.04Hz
	// Fcpu = 16MHz and Fpwm = Fcpu/(256*N)
	//	=> 61.035 = Fcpu/(256*N)
	// <=> N = 1024
	//set OCR0A PWM, fast PWM, prescaler = 1024, non-inverted
	TCCR0B = 0x05;
	TCCR0A = 0b10100011; // to activate OCR0A and OCR0B
	// Computation of the PWM in non-inverting mode //timer0 pin5
	if (dutyCycle == 0)
	{
		OCR0A = 0;
		OCR0B = 0;
	}
	else{
		OCR0A = (int) (dutyCycle * 256)/100 - 1;
		OCR0B = (int) (dutyCycle * 256)/100 - 1;
	}
}