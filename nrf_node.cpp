#include "nrf_node.h"

// SPIClass vspi = SPIClass(VSPI);
RF24 radio_01 = RF24(NRF_01_CE, NRF_01_CSN);
RF24 radio_02 = RF24(NRF_02_CE, NRF_02_CSN);
RF24 radio_03 = RF24(NRF_03_CE, NRF_03_CSN);

bool initNRFNodes(uint8_t power) {
  sysLogger(INFO, "NRF initiation started");
  const uint8_t csnPins[] = {NRF_01_CSN, NRF_02_CSN, NRF_03_CSN};
  const uint8_t cePins[]  = {NRF_01_CE,  NRF_02_CE,  NRF_03_CE};

  for (uint8_t i = 0; i < 3; i++) {
    pinMode(csnPins[i], OUTPUT);
    digitalWrite(csnPins[i], HIGH); // HIGH = SPI deselected
    pinMode(cePins[i], OUTPUT);
    digitalWrite(cePins[i], LOW);   // LOW = RF standby
  }

  SPI.begin(NRF_SCK, NRF_MISO, NRF_MOSI);

  if (!radio_01.begin(&SPI)){
    sysLogger(ERR, "NRF 01 Failed to start..!");
    return 0;
  }
  sysLogger(INFO, "NRF 01 started");

  if (!radio_02.begin(&SPI)){
    sysLogger(ERR, "NRF 02 Failed to start..!");
    return 0;
  }
  sysLogger(INFO, "NRF 02 started");

  if (!radio_03.begin(&SPI)){
    sysLogger(ERR, "NRF 03 Failed to start..!");
    return 0;
  }
  sysLogger(INFO, "NRF 03 started");

  radio_01.setPALevel(power);
  radio_02.setPALevel(power);
  radio_03.setPALevel(power);

  sysLogger(INFO, "NRF initiation completed");
  return 1;
}

bool initNRFNodes(uint8_t power, uint8_t payloadSize) {
  if (!initNRFNodes(power)) {
    return 0;
  }
  radio_01.setPayloadSize(payloadSize);
  return 1;
}

void setNRFNetwork(const uint8_t* address) {
  radio_01.stopListening(address);  // TX Mode only with address
}

void setNRFNetwork(uint8_t pipe, const uint8_t* address) {
  radio_01.openReadingPipe(pipe, address);  // RX Mode on pipe and address
  radio_01.startListening();
}

bool broadcastNRFData(const void* dataBuffer, uint8_t length) {
  return radio_01.write(dataBuffer, length);
}
