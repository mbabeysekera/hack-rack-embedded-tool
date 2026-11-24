#ifndef SYS_INIT_h_
#define SYS_INIT_h_

#include <Arduino.h>
#include "sys_config.h"
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "pcf8574.h"

extern SPIClass hspi;
extern Adafruit_ST7735 tft;

typedef enum {
  INFO = 0,
  WARN = 1,
  ERR = 2,
} LogType;

void sysInit();
void sysDisplayInfo();
void sysMessagePrint(uint16_t color, const char* message);
void sysLogFormatter(uint16_t color, const char* messageType, const char* message);
void sysLogger(LogType type, const char* message);

#endif