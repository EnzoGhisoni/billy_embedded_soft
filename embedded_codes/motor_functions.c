/*
 * motor_functions.c
 *
 * Created: 05/12/2020 15:39:58
 *  Author: Enzo
 */ 
#include "motor_functions.h"
/*****************************************************************************          
 *          ______     
 *   enA  -|      |- VCC1
 *   IN1  -|      |- IN4
 *   OUT1 -|      |- OUT4
 *   GND  -|      |- GND
 *   GMD  -|      |- GND
 *   OUT2 -|      |- OUT3
 *   IN2  -|      |- IN3
 *   VCC2 -|______|- enB
 *   
 enX = High will make the engine spin, Low will make it stop but can control the speed with a 
 (PWM maximum possible values are 0 to 255)
 OUT1(+) and OUT2(-) are the output for motor 1
 OUT4(+) and OUT3(-) are the output for motor 2
 
 IN1      IN2  Spinning Direction
 Low(0)  Low(0)  Motor OFF
 High(1) Low(0)  Forward
 Low(0)  High(1) Backward
 High(1) High(1) Motor OFF
 
 ******************************************************************************/
const unsigned char HIGH = 1;
const unsigned char LOW = 0;
const unsigned char straight = 0;
const unsigned char back = 1;
const unsigned char left = 2;
const unsigned char right = 3;
// Motor A connections
int enA = PIND5;
int in1 = PINB0;
int in2 = PIND7;

// Motor B connections
int enB = PIND6;
int in3 = PINB1;
int in4 = PIND4;
//int sens = 0;
/*****************************************************************************
	This functions will change the motion of the robot according to the input
	argument
	For the sens argument:
	- 0 = straight
	- 1 = back
	- 2 = turn left
	- 3 = turn right
	if the speed is equal to 0, the robot is stopped
 ******************************************************************************/
void move_robot(unsigned char motorSpeed, unsigned char sens) {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  
  //analogWrite(enA, motorSpeed);
  //analogWrite(enB, motorSpeed);
  configPWM_Duty(motorSpeed);
  if(sens == 0){
	  //USART_send('Y');
  }
  if(motorSpeed == 90){
	  //USART_send('Z');
  }
  // If forward is clicked
  if(motorSpeed>0 && sens == straight){
    // Turn on motor A & B
    select_type_move(HIGH, LOW, HIGH, LOW);
	USART_send('0');
  }
  // If backward is clicked
  if(motorSpeed>0 && sens == back){
    // Change motor directions
    select_type_move(LOW, HIGH, LOW, HIGH);
	USART_send('1');
    // Delay of 10 ms
	
  }
  // If turn left is clicked
  if(motorSpeed> 0 && sens == left){
    select_type_move(LOW, HIGH, HIGH, LOW);
	USART_send('2');
    // Delay of 10 ms

  }
  
  // If turn right is clicked
  if(motorSpeed>0 && sens == right){
	select_type_move(HIGH, LOW, LOW, HIGH);
    USART_send('3');
  }
  
  if(motorSpeed == 0){
    //Stop motor at the end
    stop_robot();
  }
  
  else{
	  USART_send('N');
  }
  
  
}

/*****************************************************************************          
	This functions changes the stage of the inX pins in function of the input
	arguments
 ******************************************************************************/
void select_type_move(int in1_state, int in2_state, int in3_state, int in4_state){
	
	if (in1_state == LOW)
	{
		PORTB &= ~(1<<in1);
	}
	else{
		PORTB |= (1<<in1);
	}
	
	if (in2_state == LOW)
	{
		PORTD &= ~(1<<in2);
	}
	else{
		PORTD |= (1<<in2);
	}
	
	if (in3_state == LOW)
	{
		PORTB &= ~(1<<in3);
	}
	else{
		PORTB |= (1<<in3);
	}
	
	if (in4_state == LOW)
	{
		PORTD &= ~(1<<in4);
	}
	else{
		PORTD |= (1<<in4);
	}
	//TimerDelay10ms();
	/*
	
	PORTB = in1_state << in1;
	PORTD = in2_state << in2;
	PORTB = in3_state << in3;
	PORTD = in4_state << in4;
	*/
}

/*****************************************************************************          
	This functions stops the robot by writing 0 to all registers motor control
 ******************************************************************************/
void stop_robot(){
	USART_send('S');
	PORTB &= ~(1<<in1);
	PORTD &= ~(1<<in2);
	PORTB &= ~(1<<in3);
	PORTD &= ~(1<<in4);
	
}

/*****************************************************************************          
	This functions changes the angle of the servo to change the camera orientation
 ******************************************************************************/
void changeServoValue(){
	uint16_t analogicValue;
	analogicValue = measurePotentiometerValue();
	OCR1B = (analogicValue * 5);
}