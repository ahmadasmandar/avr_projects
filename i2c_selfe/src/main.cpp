#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/sfr_defs.h>
#include "USART.h"
bool check;

// #define F_CPU 8000000UL
#define fcli2c 100000UL
#define _BV(bit) (1 << (bit))

void waitToComplete(void)
{
  // while (!(TWCR & (1<<  TWINT)));
  loop_until_bit_is_set(TWCR, TWINT);
}
void initI2C(uint8_t freqMhz)
{
  // TWBR = ((freqMhz*1000000) / 2 * fcli2c) - 8;
  TWBR = 72; /* set bit rate, see p. 242 */
  /* 8MHz / (16+2*TWBR*1) ~= 100kHz */
  TWCR |= (1 << TWEN); /* enable */
}
void sendStart(void)
{
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
  waitToComplete();
}

bool sendData(uint8_t data)
{
  TWDR = data;
  TWCR = (_BV(TWINT) | _BV(TWEN));
  waitToComplete();
  if ((TWSR & 0xF8) == 0x18 || (TWSR & 0xF8) == TW_MR_SLA_ACK)
    return true;
  else
  {
    return false;
  }
}

uint8_t readAcknowlage(void)
{
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWEA));
  waitToComplete();
  return (TWDR);
}

uint8_t i2cReadNoAck(void)
{
  TWCR = (_BV(TWINT) | _BV(TWEN));
  waitToComplete();
  return (TWDR);
}

void stopI2c(void)
{
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTO));
}

uint8_t rec1, rec2, rec3;
int main(void)

{
  initI2C(16);
  initUSART();
  printString("Start testing Selfe");
  DDRB = 0xff;

  while (1)
  {
    // for (size_t i = 0; i < 255; i++)
    // {
    sendStart();
    sendData(16);
    sendStart();
    sendData(17);
    rec1 = i2cReadNoAck();
    // rec2 = readAcknowlage();
    // rec3 = readAcknowlage();
    stopI2c();
    transmitByte(rec1);
    printByte(rec1);
    // printByte(rec2);
    // printByte(rec3);
    // if (check)
    // {
    //   printString("Device found on : ");
    //   // printByte(i);
    //   // _delay_ms(10);
    // }

    // _delay_ms(10);
    // printByte(check);
    // printByte(TWSR & 0xF8);
    _delay_ms(1000);
    // }
  }

  return 0;
}