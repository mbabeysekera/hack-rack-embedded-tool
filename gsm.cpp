#include "gsm.h"

static char gsm_rx_buffer[GSM_RX_BUFFER_SIZE];

int8_t gsmWrite(const char* command) {
  uint8_t tempIndex = 0;

  busSelect(GSM_BUS);
  busControl(BUS_ENABLE);
  memset(gsm_rx_buffer, 0, GSM_RX_BUFFER_SIZE);
  //Clear RX buffer after selecting the bus
  while (Serial2.available()) {
    Serial2.read();
  }

  Serial2.println(command);
  unsigned long timeStart = millis();

  while (millis() - timeStart < GSM_CMD_TIMEOUT) {
    while (Serial2.available()) {
      if (tempIndex >= (GSM_RX_BUFFER_SIZE - 1)) {
        busControl(BUS_DISABLE);
        sysLogger(ERR, "GSM exceeded buffer");
        return -1;
      }
      gsm_rx_buffer[tempIndex] = Serial2.read();
      tempIndex++;
      gsm_rx_buffer[tempIndex] = '\0';
    }

    if (tempIndex > 0 && (strstr(gsm_rx_buffer, "OK\r\n") != NULL || strstr(gsm_rx_buffer, "ERROR\r\n") != NULL)) {
      break;
    }
    delay(1);
  }
  busControl(BUS_DISABLE);
  if (tempIndex == 0) {
    sysLogger(ERR, "GSM response timeout");
    return 0;
  }
  Serial.println(gsm_rx_buffer);
  Serial.flush();
  return 1;
}

bool gsmWriteAndValidateResponse(const char* command, const char* response) {
  gsmWrite(command);
  if (strstr(gsm_rx_buffer, response) != NULL) {
    sysLogger(INFO, "GSM response valid");
    return true;
  } else {
    sysLogger(ERR, "GSM response invalid");
    return false;
  };
}

void gsmRead() {
  busSelect(GSM_BUS);
  while (Serial2.available()) {
    Serial.write(Serial2.read());
  }
}

void gsmIsReady() {
  uint32_t timeStart = millis();
  while (millis() - timeStart < 10000) {
    sysLogger(INFO, "GSM initializing...");
    if (gsmWriteAndValidateResponse("AT", "OK\r\n") > 0) {
      sysLogger(INFO, "GSM module ready");
      return;
    } else {
      sysLogger(ERR, "GSM module failed");
    };
  }
  sysLogger(ERR, "GSM module timeout!");
}

void gsmStopCommandEcho() {
  sysLogger(INFO, "GSM echo stopped");
  gsmWrite("ATE0");
}

void gsmDisable() {
  sysLogger(INFO, "GSM disable radio");
  gsmWrite(GSM_TURN_OFF_CELL);
}

void gsmEnableRadio() {
  sysLogger(INFO, "GSM enable radio");
  gsmWrite(GSM_TURN_ON_RF);
}

void gsmEnableFlightMode() {
  sysLogger(INFO, "GSM flight mode on");
  gsmWrite(GSM_TURN_OFF_RF);
}

void gsmGetSIMStatus() {
  sysLogger(INFO, "GSM sim status");
  gsmWrite(GSM_SIM_STATUS);
}

void gsmGetSignalStrength() {
  sysLogger(INFO, "GSM signal strength");
  gsmWrite(GSM_GET_SIGNAL_STRENGTH);
}