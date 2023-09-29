/*
 * ADC.h
 *
 * Created: 11/12/2020 09:42:13
 *  Author: Enzo
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
uint16_t measurePotentiometerValue();
void initADC(void);


#endif /* ADC_H_ */