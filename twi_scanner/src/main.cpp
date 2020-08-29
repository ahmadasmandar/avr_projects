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
  printString("Start Transmiting");
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
      // transmitByte(checkErr());

      // PORTB =i2cReadAck();
      // transmitByte('\r');
      // printByte(i2cReadNoAck());
      // transmitByte('\r');
      // if (i2cReadAck() < 255)
      // {
      //   printString("adress found and is : ");
      //   PORTB |=i2cReadAck();
      // }
      i2cStop();
      // transmitByte(' ');
      _delay_ms(50);
    }
  }
  return 0;
}
