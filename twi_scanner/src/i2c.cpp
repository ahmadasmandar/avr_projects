#include "i2c.h"
#include<avr/sfr_defs.h>
#include <util/twi.h>
#include "USART.h"

void initI2C(void)
{
    TWBR = 72; /* set bit rate, see p. 242 */
    /* 8MHz / (16+2*TWBR*1) ~= 100kHz */
    TWCR |= (1 << TWEN); /* enable */
}
void i2cWaitForComplete(void)
{
    loop_until_bit_is_set(TWCR, TWINT);
}
void i2cStart(void)
{
    TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
    i2cWaitForComplete();
}
void i2cStop(void)
{
    TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTO));
}
uint8_t i2cReadAck(void)
{
    TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWEA));
    i2cWaitForComplete();
    return (TWDR);
}
uint8_t i2cReadNoAck(void)
{
    TWCR = (_BV(TWINT) | _BV(TWEN));
    i2cWaitForComplete();
    return (TWDR);
}
void i2cSend(uint8_t data)
{
    TWDR = data;
    TWCR = (_BV(TWINT) | _BV(TWEN)); /* init and enable */
    i2cWaitForComplete();
}
uint8_t checkErr(void)
{
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
        
        {
          return true;
        }
      else
      {
        return false;

      }
      TWCR = (1 << TWINT) | (1 << TWEN);
}


