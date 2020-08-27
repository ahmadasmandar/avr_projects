/*
 * serial.h
 *
 * Created: 23.08.2020 21:36:46
 *  Author: Ahmad Asmandar
 */ 

#ifndef SERIAL_H_
#define SERIAL_H_
void initUsart();
void sendByte(unsigned char data);
unsigned char receiveByte(void);

#endif /* SERIAL_H_ */