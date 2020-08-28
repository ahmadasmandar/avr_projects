/*
 * serial_atmega328p.c
 *
 * Created: 27.08.2020 20:31:25
 * Author : Ahmad Asmandar
 */

#include <avr/io.h>
#define F_CPU 8000000L

#include <util/delay.h>
void USART_Init(unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    /*Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

int main(void)
{
    /* Replace with your application code */

    // put your setup code here, to run once:
    USART_Init(8);
    while (1)
    {
        USART_Transmit('a');
		USART_Transmit('\r');
		USART_Transmit('\n');
        _delay_ms(500);
    }
}
