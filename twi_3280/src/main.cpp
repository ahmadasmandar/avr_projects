#include <Arduino.h>
#include <avr/io.h>
#define USE_2X

// #define __AVR__Atmega328p__

// #include <util/delay.h>
#include "USART.h"

// void USART_Init(unsigned int ubrr)
// {
//   /*Set baud rate */
//   UBRR0H = (unsigned char)(ubrr >> 8);
//   UBRR0L = (unsigned char)ubrr;
//   /*Enable receiver and transmitter */
//   UCSR0B = (1 << RXEN0) | (1 << TXEN0);
//   /* Set frame format: 8data, 2stop bit */
//   UCSR0C = (0 << USBS0) | (3 << UCSZ00);
// }

// void USART_Transmit(unsigned char data)
// {
//   /* Wait for empty transmit buffer */
//   while (!(UCSR0A & (1 << UDRE0)))
//     ;
//   /* Put data into buffer, sends the data */
//   UDR0 = data;
// }

void setup()
{
  // put your setup code here, to run once:
  // USART_Init(51);
  initUSART(8);
  DDRB |= (1 << PB0);
  PORTB |= (1 << PB0);
}

void loop()
{
  // put your main code here, to run repeatedly:

  transmitByte('a');
  transmitByte('\r');
  transmitByte('\n');
  printString("Ahmad Hallo");
  transmitByte('\r');
  transmitByte('\n');
  delay(500);
  PORTB ^= (1 << PB0);
}