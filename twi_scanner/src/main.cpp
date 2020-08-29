/*
Written by Ahmad Asmandar 29.08.2020
Ilmenau

*/



#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "i2c.h"
uint16_t ack = 0;

int main(void)
{

  initUSART();
  transmitByte('\r');
  transmitByte('\n');
  printString("Start Scanning");
  initI2C();
  transmitByte('\r');
  transmitByte('\n');
  DDRB = 0xFF;

  while (1)
  {

    for (int i = 0; i < 255; i++)
    {
      i2cStart();
      i2cSend(i);
      if (!checkErr())
      {
        printString("adress found on: ");
        printByte(i);
      }

      i2cStop();
      _delay_ms(50);
    }
  }
  return 0;
}
