#include "sys_init.h"

static uint8_t displayLinesCounter = 0;

SPIClass hspi = SPIClass(HSPI);
Adafruit_ST7735 tft = Adafruit_ST7735(&hspi, TFT_CS, TFT_DC, TFT_RST);

void sysInit() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX2, TX2);
  Wire.begin(SDA_PIN, SCL_PIN);
  initPCF8574();
  hspi.begin(TFT_SCLK, -1, TFT_MOSI, -1);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);

  tft.enableDisplay(false);
}

void sysDisplayInfo() {
  tft.enableDisplay(true);
  writePCF8574Pin(BACKLIT_PIN, true); 
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("CoolBreeZ");
  tft.println("RF: 2.4GHz/WiFi/BLE");
  tft.println("GPS: Standard");
  tft.println();
}

void sysMessagePrint(uint16_t color, const char* message) {
  tft.setTextColor(color);
  tft.setTextSize(1);
  tft.print(message);
}

void sysLogFormatter(uint16_t color, const char* messageType, const char* message) {
  if (displayLinesCounter >= 15) {
    displayLinesCounter = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(1);
  }
  displayLinesCounter++;
  Serial.print(messageType);
  Serial.println(message);
  sysMessagePrint(color, messageType);
  sysMessagePrint(color, message);
  tft.println();
}

void sysLogger(LogType type, const char* message) {
  switch (type) {
    case INFO: sysLogFormatter(ST7735_GREEN, "info: ", message); break;
    case WARN: sysLogFormatter(ST7735_YELLOW, "warn: ", message); break;
    case ERR: sysLogFormatter(ST7735_RED, "err: ", message); break;
  }
}