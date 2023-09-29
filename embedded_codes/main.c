/*
 * Final_project.c
 *
 * Created: 05/12/2020 14:09:15
 * Author : Enzo
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "communication.h"
#include "motor_functions.h"
#include "GPIO.h"

int main(void)
{
	int robotSpeed = 0;
	int sens = 0;
	//unsigned char* prev_message = {0, 0};
	char prev_message[2];
	int message = 0;
	initGPIO();
	initADC();
	configPWM();
	USART_init();
	//unsigned char* receivedMessage;
	char receivedMessage[10];
	
	//stop_robot();
    //receivedMessage = USART_receive(); // Wait until data is received
	
    while (1)
    {	
		//receivedMessage = USART_receive_string(); // Wait until data is received
		
		//USART_receive_string(*receivedMessage); // Wait until data is received
		// Wait until data is received
		//sens = receivedMessage[0];
		//robotSpeed = receivedMessage[1];
		char num[2];
		int i = 0;
		//while(UDR0 != " " && i<2)
		while(UDR0 != ' ' && i<2)
		{
			while(!(UCSR0A & (1<<RXC0))); // Wait to receive data
			//USART_send(UDR0);
			receivedMessage[i] = UDR0;
			USART_send((char)i);
			//USART_send(receivedMessage[i]);
			i++;
		}
		//strcpy(num, receivedMessage);
		//strcpy(num, "12");
		USART_send(receivedMessage[0]);
		USART_send(receivedMessage[1]);
		message = atoi(receivedMessage);
		//message = atoi(num);
		USART_send(message);
		//message = atoi(*receivedMessage);
		//message = 10 * atoi(sens) + atoi(robotSpeed);
		
		if(message < 100){
			//receivedMessage = prev_message;
			receivedMessage[0] = prev_message[0];
			receivedMessage[1] = prev_message[1];
		}
		//USART_send(sens);
		//USART_send(robotSpeed);
		
		//sens = atoi(sens);
		//robotSpeed = atoi(robotSpeed);
		
		
		
		/*
			We decode the message received by SUART encoded on a int
			the int is between 0 and 39 in the format XY
			X is the direction 0 straight, 1 back, 2 left, 3 right
			Y is the speed between 0 and 9
		*/
		
		// Get the speed of the robot from the message
		robotSpeed = getSpeedFromMessage(message);
		// Get the sens of the robot from the message
		sens = getSens(message);
		
		// Control the motor of the robot
		move_robot(robotSpeed, sens);
		
		// Actualize the value of the servomotor to turn the camera
		changeServoValue();
		prev_message[0] = receivedMessage[0];
		prev_message[1] = receivedMessage[1];
		
    }
}

/***********************************************************************************************************
	We define the hardware interrupt on the Vector INT0_vect (hardware interrupt port on Arduino pin 2)
************************************************************************************************************/

ISR (INT0_vect)          //External interrupt_zero ISR
{
	// To stop the robot
	move_robot(0, 0);
}