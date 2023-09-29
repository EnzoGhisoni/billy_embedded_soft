/*
 * communication.c
 *
 * Created: 05/12/2020 15:27:54
 *  Author: Enzo
 */
#include "communication.h"

#define F_CPU 16000000UL
#define BAUDRATE 4800
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART_init(void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8); // set baud rate
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable transmit
	UCSR0C = (3 << UCSZ00);				  // set 8-bit (default)
}

/**********************************************************************
	This function will get the data from the serial communication (UART)
	and will return the character store in the register UDR0
**********************************************************************/
unsigned char USART_receive(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		;		 // Wait to receive data
	return UDR0; // Read data from UDR
}

void USART_receive_string(unsigned char *ReceivedString)
{
	// char ReceivedString[40];
	// unsigned char* ReceivedString;
	int i = 0;
	while (UDR0 != " ")
	{
		while (!(UCSR0A & (1 << RXC0)))
			; // Wait to receive data
		// USART_send(UDR0);

		ReceivedString[i] = UDR0;
		// USART_send(ReceivedString[i]);
		i++;
	}
	// ReceivedString = UDR0;
	// return ReceivedString; // Read data from UDR
}

char USART_receive_digit_value()
{
	char ReceivedString[10];
	// unsigned char* ReceivedString;
	int i = 0;
	while (UDR0 != " ")
	{
		while (!(UCSR0A & (1 << RXC0)))
			; // Wait to receive data
		// USART_send(UDR0);
		ReceivedString[i] = UDR0;
		// USART_send(ReceivedString[i]);
		i++;
	}
	// ReceivedString = UDR0;
	return ReceivedString; // Read data from UDR
}

/**********************************************************************
	This function will send a data (a char) via UART which
	will be visualizable in the terminal
**********************************************************************/
void USART_send(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;		 // check if data is sent
	UDR0 = data; // load new data to transmit
}

unsigned char getSpeedFromMessage(int message)
{
	int robot_speed_number = 0;
	robot_speed_number = message % 10;
	robot_speed_number = robot_speed_number * 10;
	return robot_speed_number;
}
unsigned char getSens(int message)
{
	int sens = 0;
	sens = message / 10;
	return sens;
}
