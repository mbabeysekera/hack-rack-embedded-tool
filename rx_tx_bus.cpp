#include "rx_tx_bus.h"

void busControl(const uint8_t control) {
  if (!control) {
    writePCF8574Pin(4, false);
  } else {
    writePCF8574Pin(4, true);
  }
  delay(10);
}

void busSelect(const uint8_t bus) {
  switch (bus) {
    case 0:
      {
        writePCF8574Pin(0, true);
        writePCF8574Pin(5, false);
        writePCF8574Pin(6, false);
      }
      break;
    case 5:
      {
        writePCF8574Pin(0, false);
        writePCF8574Pin(5, true);
        writePCF8574Pin(6, false);
      }
      break;
    case 6:
      {
        writePCF8574Pin(0, false);
        writePCF8574Pin(5, false);
        writePCF8574Pin(6, true);
      }
      break;
  }
  delay(10);
}
