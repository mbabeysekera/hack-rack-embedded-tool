#ifndef SYS_CONFIG_h_
#define SYS_CONFIG_h_

#include <Arduino.h>

// Control pin definitions
#define TFT_CS 15
#define TFT_DC 4
#define TFT_RST 2

// HSPI Bus pin definitions
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14

// Define Custom Colors (RGB565 format)
#define ST7735_BLACK 0x0000
#define ST7735_BLUE 0x001F
#define ST7735_RED 0xF800
#define ST7735_GREEN 0x07E0
#define ST7735_CYAN 0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW 0xFFE0
#define ST7735_WHITE 0xFFFF

#define SDA_PIN 21
#define SCL_PIN 22

#define RX2 16
#define TX2 17

#define BACKLIT_PIN 7

#endif