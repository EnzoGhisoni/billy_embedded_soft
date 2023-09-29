/*
 * configuration_GPIO.c
 *
 * Created: 05/12/2020 15:34:44
 *  Author: Enzo
 */ 
/*****************************************************************************          
 *          ______     
 *   ENA  -|      |- VCC1
 *   IN1  -|      |- IN4
 *   OUT1 -|      |- OUT4
 *   GND  -|      |- GND
 *   GMD  -|      |- GND
 *   OUT2 -|      |- OUT3
 *   IN2  -|      |- IN3
 *   VCC2 -|______|- ENB
 *   
 ENX = High will make the engine spin, Low will make it stop but can control the speed with a PWM
 OUT1(+) and OUT2(-) are the output for motor 1
 OUT4(+) and OUT3(-) are the output for motor 2
 
 IN1      IN2    Spinning Direction
 Low(0)  Low(0)  Motor OFF
 High(1) Low(0)  Forward
 Low(0)  High(1) Backward
 High(1) High(1) Motor OFF

In this configuration:
// Motor A connections
enA = PIND5;
in1 = PINB0;
in2 = PIND7;

// Motor B connections
enB = PIND6;
in3 = PINB1;
in4 = PIND4;
 ******************************************************************************/
#include "GPIO.h"

/**********************************************************************************************************
	This function initializes the GPIO
**********************************************************************************************************/
void initGPIO(){
	//H-bridge direction control
	
	DDRD |= (1 << PIND4) | (1 << PIND7);
	DDRB |= (1 << PINB0)| (1 << PINB1);
	PORTB|= (1 << PINB1);
	PORTB|= (1 << PINB0);
	//OCR0A PWM, set PortD.5 and PortD.6 output
	DDRD |= (1 << PIND5) | (1 << PIND6);
	
	// Servo control on pin 10 (PINB2)
	DDRB |= (1 << PINB2);
	
}

