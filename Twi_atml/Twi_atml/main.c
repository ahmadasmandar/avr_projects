#define F_CPU 8000000UL
#define BAUD 9600
#ifndef __AVR_ATmega32__
#define __AVR_ATmega32__
#endif

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#include "i2c.h"
// #include "serial.h"
#include "USART.h"

void i2cSendmain(uint8_t data)
{
	TWDR = data;
	TWCR = (_BV(TWINT) | _BV(TWEN)); /* init and enable */
	i2cWaitForComplete();
}
void i2cSendStringmain(char data[])
{
	int size = sizeof(data);
	for (int i = 0; i < size; i++)
	{
		i2cSend(data[i]);
	}
}

int main(void)

{
	// Void Setup
	initUSART();
	initI2C();

	// Void loop
	while (1)
	{
		i2cStart();
		//Send Adress
		i2cSend(18);
		//send Data
		char data[] = ("ahmad how are you today lets's see if it works..");
		//int size = sizeof(data);
		//transmitByte(size);
		//transmitByte('\n');
		//transmitByte('\r');

		// for (int i = 0; i < size; i++)
		uint8_t i = 0;
		while (data[i])
		{
			i2cSend(data[i]);
			transmitByte(data[i]);
			i++;
			_delay_ms(5);
		}
		transmitByte('\n');
		transmitByte('\r');

		// {
		// 	i2cSend(data[i]);
		// 	transmitByte(data[i]);
		// }

		i2cStop();
		_delay_ms(500);
	}
	return 0;
}
