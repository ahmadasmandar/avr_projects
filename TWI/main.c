#define F_CPU 8000000UL
#ifndef __AVR_ATmega32__
#define __AVR_ATmega32__
#endif

#include <avr/io.h>
#include "i2c.h"

int main(void)

{
	initI2C();
    while (1)
    {
        
    }
    return 0;
}
