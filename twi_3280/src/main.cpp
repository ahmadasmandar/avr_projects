#include <Arduino.h>
#include <avr/io.h>

// #define __AVR__Atmega328p__

// #include <util/delay.h>
#include "USART.h"
// #define BAUD 57600

void setup()
{
  // put your setup code here, to run once:
  // USART_Init(51);
  initUSART();
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