/*
 * communication.h
 *
 * Created: 05/12/2020 17:02:28
 *  Author: Enzo
 */ 


#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include <avr/io.h>
unsigned char USART_receive(void);
void USART_init(void);
unsigned char getSpeedFromMessage(int message);
unsigned char getSens(int message);
void USART_send(unsigned char data);
//unsigned char* USART_receive_string(void);
void USART_receive_string(unsigned char* ReceivedString);
char USART_receive_digit_value();
#endif /* COMMUNICATION_H_ */