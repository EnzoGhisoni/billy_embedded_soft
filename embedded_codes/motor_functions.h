/*
 * motor_functions.h
 *
 * Created: 05/12/2020 15:40:29
 *  Author: Enzo
 */ 


#ifndef MOTOR_FUNCTIONS_H_
#define MOTOR_FUNCTIONS_H_
#include <avr/io.h>
#include "PWM.h"
#include "ADC.h"
#include "Timers.h"
#include "communication.h"
void move_robot(unsigned char motorSpeed, unsigned char sens);
void select_type_move(int in1_state, int in2_state, int in3_state, int in4_state);
void stop_robot();
void changeServoValue();



#endif /* MOTOR_FUNCTIONS_H_ */