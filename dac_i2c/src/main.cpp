#include <Arduino.h>
#include "i2cmaster.h"
#include "USART.h"
#include "util/delay.h"
#define CONV_REG 0b0000000 //This register holds the result of the most recent conversion.
#define ALERT_REG 0b00000001
#define CONFIG_REG 0b0000010
#define LOW_REG 0b0000011
#define HIGH_REG 0b0000100
#define HYST_REG 0b0000101
#define LCONV_REG 0b0000110
#define HCONV_REG 0b0000111

#define SLAVE_ADRESS_READ 0b10101011
#define SLAVE_ADRESS_wRITE 0b10101010
#define MAX 100

uint8_t adres_flag = 0;

int main(void)
{

  initUSART();
  i2c_init();
  _delay_ms(10);
  uint8_t highByte, lowByte;
  // uint8_t read_reg;
  char buf[MAX];

  while (1)
  {
    adres_flag = i2c_start(SLAVE_ADRESS_wRITE);

    //! here to check the Adress from the Slave Device
    //?0 mean success
    //?1 mean Error

    // printByte(adres_flag);
    // if (!adres_flag)
    // {
    //   printString("success adress was found !!!!");
    //   printString("Adress checked and ready to operate");
    // }
    // else
    // {
    //   printString("there is error adress not found");
    // }
    // i2c_write(ALERT_REG);
    // i2c_write(0b000010);
    //!config the ADC Registers
    i2c_write(ALERT_REG);
    i2c_write(0b00000010);

    i2c_rep_start(SLAVE_ADRESS_wRITE);
    i2c_write(CONFIG_REG);
    i2c_write(0b0001100);
    i2c_stop();
    // Try to set the Highlimit !! but not working
    // i2c_start(SLAVE_ADRESS_wRITE);
    // i2c_write(HIGH_REG);
    // i2c_write(0b00011111);
    // i2c_write(0b11111111);
    // _delay_ms(50);
    // i2c_stop();

    //! call the Data Register in ADC
    i2c_start(SLAVE_ADRESS_wRITE);
    i2c_write(CONV_REG);
    //!Read the Tow Bytes data and combine them
    i2c_rep_start(SLAVE_ADRESS_READ);
    _delay_ms(10);
    highByte = i2c_readAck();
    lowByte = i2c_readNak();
    i2c_stop();
    //function to check the overflow but Error
    // if (highByte & _BV(7))
    // {
    //   printString("Overflow!!!!");
    // }

    //! Combine the Tow Bytes
    uint16_t combined = highByte << 8 | lowByte;
    printWord(combined);
    //calculate the voltage value and convert it from Float to String
    //! Take care to get float Values you need to add .00 after the number
    //otherwise you will get just INT!!!

    float temp = (combined * 5) / 4095.0000;
    //? the magic function to convert float to String!!!
    dtostrf(temp, 1, 5, buf);
    printString(buf);
    // printBinaryByte(highByte);
    // printBinaryByte(lowByte);

    _delay_ms(1000);
  }

  return 0;
}