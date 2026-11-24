#ifndef GPS_h_
#define GPS_h_

#include <Arduino.h>
#include "sys_init.h"
#include "rx_tx_bus.h"

// #define GPS_RX_BUFFER_SIZE  128

#define GPS_BUS             BUS_01_SELECT
#define GPS_TIMEOUT         2000

void gpsWrite(const char* command);
void ingestGPSBytes(char byte);
void gpsRead();

#endif