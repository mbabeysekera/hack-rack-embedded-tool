#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "sys_init.h"

#define NRF_01_CSN 33
#define NRF_02_CSN 32
#define NRF_03_CSN 5

#define NRF_03_CE 27
#define NRF_02_CE 26
#define NRF_01_CE 25

#define NRF_SCK 18
#define NRF_MISO 19
#define NRF_MOSI 23

#define NRF_TX_MODE 0  // NRF works as a transmitter
#define NRF_RX_MODE 1  // NRF works as a receiver
#define NRF_SP_MODE 2  // NRF works as a continuous carier transmitter (no modulation)

// extern SPIClass vspi;
extern RF24 radio_01;
extern RF24 radio_02;
extern RF24 radio_03;

bool initNRFNodes(uint8_t power);
bool initNRFNodes(uint8_t power, uint8_t payloadSize);
void setNRFNetwork(const uint8_t* address);
void setNRFNetwork(uint8_t pipe, const uint8_t* address);
bool broadcastNRFData(const void* dataBuffer, uint8_t length);