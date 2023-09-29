/*
 * PWM.h
 *
 * Created: 05/12/2020 16:19:05
 *  Author: Enzo
 */ 


#ifndef PWM_H_
#define PWM_H_
#include <avr/io.h>

void configPWM();
void configPWM_Duty(float dutyCycle);


#endif /* PWM_H_ */