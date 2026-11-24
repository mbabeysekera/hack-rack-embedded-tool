#include "pcf8574.h"

uint8_t pcf8574State = 0x00;

void writePCF8574(const char byte) {
  Wire.beginTransmission(PCF8574_ADDR);
  Wire.write(byte);
  Wire.endTransmission();
}

void updatePCF8574() {
  Wire.beginTransmission(PCF8574_ADDR);
  Wire.write(pcf8574State);
  Wire.endTransmission();
}

void initPCF8574() {
  writePCF8574(0x00);
}

void writePCF8574Pin(uint8_t pinNumber, bool state) {
  if (state) {
    pcf8574State |= (1 << pinNumber);
  } else {
    pcf8574State &= ~(1 << pinNumber);
  }
  updatePCF8574();
}