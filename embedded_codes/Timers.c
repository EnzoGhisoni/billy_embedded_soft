/*
 * configuration_Timers.c
 *
 * Created: 05/12/2020 15:33:19
 *  Author: Enzo
 */ 

#include "Timers.h"
/**********************************************************************************************************
	This function allows to generate a delay of 10ms
**********************************************************************************************************/
void TimerDelay10ms(){
	unsigned char i = 0;
	while(i<25){
		TCNT0 = 206; //load the TCNT0 to set a delay (overflow - value) 231 for 10ms
		TCCR0A = 0x00;
		TCCR0B = 0x03; //Define Timer in Normal Mode with a prescaler of 64
		while ((TIFR0 & 0x01) == 0); //wait for TF0 to roll over
		TCCR0B = 0; //Shut down the timer
		TIFR0 = 1 << TOV0; //clear the flag TF0
		i++;
	}
}