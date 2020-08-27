/*
 * serial_test.c
 *
 * Created: 23.08.2020 21:34:54
 * Author : Ahmad Asmandar
 */ 
#define F_CPU 8000000UL
// #define BAUD 9600
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "serial.h"
#include <util/delay.h>



int main(void)
{

    initUsart();

    /* Replace with your application code */
    while (1) 
    {
        if ( (UCSRA & (1<<RXC)) )
        {
        uint8_t data;
        data = receiveByte();
        sendByte(data);
        data =0;
        }
        else
        {
        sendByte('a');
        _delay_ms(500);
        }
        
        

    }
    return 0;
}

