#ifndef PCF8574_h_
#define PCF8574_h_

#include <Arduino.h>
#include <Wire.h>

#ifndef PCF8574_ADDR
#define PCF8574_ADDR 0x20
#endif

void initPCF8574();
void writePCF8574(const char byte);
void updatePCF8574();
void writePCF8574Pin(uint8_t pinNumber, bool state);


#endif