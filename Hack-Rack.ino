#include "sys_config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "sys_init.h"
#include "pcf8574.h"
#include "rx_tx_bus.h"
#include "gps.h"
#include "gsm.h"
#include "nrf_node.h"

const uint8_t address[] = "node0";

void setup() {
  sysInit();
  sysDisplayInfo();
  gsmIsReady();
  gsmStopCommandEcho();
  gsmGetSIMStatus();
  gsmGetSignalStrength();
  gsmEnableFlightMode();

  initNRFNodes(RF24_PA_MAX, 4);
  setNRFNetwork(address);
}

void loop() {
  // gpsRead();
  float payload = 0.0f;
  broadcastNRFData(&payload, sizeof(payload));
  delay(100);
}
