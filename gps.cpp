#include "gps.h"

// static char gps_rx_buffer[GPS_RX_BUFFER_SIZE];
static uint8_t nmeaFieldCounter = 0;
static uint8_t arrayIdx = 0;
static bool isNMEAString = false;
static uint8_t parityCheck = 0x00;

struct GPSAttributes {
  char nmeaIdf[6];
  char latitude[15];
  char longitude[15];
};

static GPSAttributes gpsAttr;

void gpsWrite(const char* command) {
  busSelect(GPS_BUS);
  Serial2.println(command);
  Serial2.flush();
  busControl(BUS_DISABLE);
}

void ingestGPSBytes(char byte) {
  if (byte == '$') {
    memset(gpsAttr.nmeaIdf, 0, sizeof(gpsAttr.nmeaIdf));
    memset(gpsAttr.latitude, 0, sizeof(gpsAttr.latitude));
    memset(gpsAttr.longitude, 0, sizeof(gpsAttr.longitude));
    nmeaFieldCounter = 0;
    arrayIdx = 0;
    isNMEAString = false;
    return;
  }
  if (byte == ',') {
    nmeaFieldCounter++;
    arrayIdx = 0;
    return;
  }
  if (nmeaFieldCounter == 0) {
    gpsAttr.nmeaIdf[arrayIdx++] = byte;
    gpsAttr.nmeaIdf[arrayIdx] = '\0';
    if (arrayIdx == 5 && strstr(gpsAttr.nmeaIdf, "GPRMC") != NULL) {
      isNMEAString = true;
    }
    return;
  }
  if (nmeaFieldCounter == 3 && isNMEAString == true) {
    gpsAttr.latitude[arrayIdx] = byte;
    arrayIdx++;
    gpsAttr.latitude[arrayIdx] = '\0';
    if (arrayIdx == sizeof(gpsAttr.latitude)) {
      arrayIdx = 0;
    }
    return;
  }
  if (nmeaFieldCounter == 5 && isNMEAString == true) {
    gpsAttr.longitude[arrayIdx] = byte;
    arrayIdx++;
    gpsAttr.longitude[arrayIdx] = '\0';
    if (arrayIdx == sizeof(gpsAttr.longitude)) {
      arrayIdx = 0;
    }
    return;
  }
}

void gpsRead() {
  busSelect(GPS_BUS);
  busControl(BUS_ENABLE);

  while (Serial2.available()) {
    ingestGPSBytes(Serial2.read());
  }
  Serial.print(gpsAttr.nmeaIdf);
  Serial.print(" ");
  Serial.print(gpsAttr.latitude);
  Serial.print(" ");
  Serial.println(gpsAttr.longitude);
}










