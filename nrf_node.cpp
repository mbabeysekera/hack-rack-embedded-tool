#include "nrf_node.h"

// SPIClass vspi = SPIClass(VSPI);
RF24 radio_01 = RF24(NRF_01_CE, NRF_01_CSN);
RF24 radio_02 = RF24(NRF_02_CE, NRF_02_CSN);
RF24 radio_03 = RF24(NRF_03_CE, NRF_03_CSN);

#define EN_NRF_01_NORMAL_MODE
// #define EN_NRF_02_NORMAL_MODE
// #define EN_NRF_03_NORMAL_MODE

bool initNRFNodes(uint8_t power) {
  sysLogger(INFO, "NRF init started");
  const uint8_t csnPins[] = { NRF_01_CSN, NRF_02_CSN, NRF_03_CSN };
  const uint8_t cePins[] = { NRF_01_CE, NRF_02_CE, NRF_03_CE };

  for (uint8_t i = 0; i < 3; i++) {
    pinMode(csnPins[i], OUTPUT);
    digitalWrite(csnPins[i], HIGH);  // HIGH = SPI deselected
    pinMode(cePins[i], OUTPUT);
    digitalWrite(cePins[i], LOW);  // LOW = RF standby
  }

  SPI.begin(NRF_SCK, NRF_MISO, NRF_MOSI);

  if (!radio_01.begin(&SPI)) {
    sysLogger(ERR, "NRF 01 Failed!");
    return 0;
  }
  sysLogger(INFO, "NRF 01 started");

  if (!radio_02.begin(&SPI)) {
    sysLogger(ERR, "NRF 02 Failed!");
    return 0;
  }
  sysLogger(INFO, "NRF 02 started");

  if (!radio_03.begin(&SPI)) {
    sysLogger(ERR, "NRF 03 Failed!");
    return 0;
  }
  sysLogger(INFO, "NRF 03 started");

  radio_01.setPALevel(power);
  radio_02.setPALevel(power);
  radio_03.setPALevel(power);

  // Default, keep the radios initialized, but disable TX and RX
#ifndef EN_NRF_01_NORMAL_MODE
  radio_01.ce(LOW);
#endif
#ifndef EN_NRF_02_NORMAL_MODE
  radio_02.ce(LOW);
#endif
#ifndef EN_NRF_03_NORMAL_MODE
  radio_03.ce(LOW);
#endif

  sysLogger(INFO, "NRF init completed");
  return 1;
}

bool initNRFNodes(uint8_t power, uint8_t payloadSize) {
  if (!initNRFNodes(power)) {
    return 0;
  }
#ifdef EN_NRF_01_NORMAL_MODE
  radio_01.setPayloadSize(payloadSize);
#endif
#ifdef EN_NRF_02_NORMAL_MODE
  radio_02.setPayloadSize(payloadSize);
#endif
#ifdef EN_NRF_03_NORMAL_MODE
  radio_03.setPayloadSize(payloadSize);
#endif
  return 1;
}

void setNRFNetwork(const uint8_t* address) {
#ifdef EN_NRF_01_NORMAL_MODE
  radio_01.stopListening(address);  // TX Mode only with address
#endif
#ifdef EN_NRF_02_NORMAL_MODE
  radio_02.stopListening(address);
#endif
#ifdef EN_NRF_03_NORMAL_MODE
  radio_03.stopListening(address);
#endif
}

void setNRFNetwork(uint8_t pipe, const uint8_t* address) {
#ifdef EN_NRF_01_NORMAL_MODE
  radio_01.openReadingPipe(pipe, address);  // RX Mode on pipe and address
  radio_01.startListening();
#endif
#ifdef EN_NRF_02_NORMAL_MODE
  radio_02.openReadingPipe(pipe, address);  // RX Mode on pipe and address
  radio_02.startListening();
#endif
#ifdef EN_NRF_03_NORMAL_MODE
  radio_03.openReadingPipe(pipe, address);  // RX Mode on pipe and address
  radio_03.startListening();
#endif
}

// Transmit data to any supported nrf node
bool broadcastNRFData(const void* dataBuffer, uint8_t length) {
#ifdef EN_NRF_01_NORMAL_MODE
  float payload = 0.1f;
  bool isOk = radio_01.write(&payload, length);
  // radio_01.printPrettyDetails();
#endif
#ifdef EN_NRF_02_NORMAL_MODE
  float payload = 0.2f;
  bool isOk = radio_02.write(&payload, length);
  // radio_02.printPrettyDetails();
#endif
#ifdef EN_NRF_03_NORMAL_MODE
  float payload = 0.3f;
  bool isOk = radio_03.write(&payload, length);
  // radio_03.printPrettyDetails();
#endif
  sysLogger(INFO, "NRF broadcast done");
  return isOk;
}
