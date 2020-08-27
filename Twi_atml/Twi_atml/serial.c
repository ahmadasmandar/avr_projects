/*
 * serial.c
 *
 * Created: 23.08.2020 21:47:25
 *  Author: Ahmad Asmandar
 */

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include "serial.h"

void initUsart()
{

    UBRRH = (51 >> 8);
    UBRRL = 51;

    UCSRA &= ~(1 << U2X);

    UCSRB = (1 << RXEN) | (1 << TXEN);
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}

void sendByte(unsigned char data)
{
    loop_until_bit_is_set(UCSRA, UDRE);
    // while (!(UCSRA & (1 << UDRE)))
    //     ;
    UDR = data;
}

// unsigned char receiveByte(void)
// {
//     loop_until_bit_is_set(UCSRA, RXC);
//     return UDR;
// }