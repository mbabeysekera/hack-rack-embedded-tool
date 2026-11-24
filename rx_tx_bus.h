#ifndef RX_RX_BUS_h_
#define RX_RX_BUS_h_

#include <Arduino.h>
#include "pcf8574.h"

#define BUS_DISABLE   1
#define BUS_ENABLE    0
#define BUS_00_SELECT 0
#define BUS_01_SELECT 5
#define BUS_10_SELECT 6

void busControl(const uint8_t control);
void busSelect(const uint8_t bus);

#endif