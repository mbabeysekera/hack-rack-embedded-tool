#ifndef GSM_h_
#define GSM_h_

#include <Arduino.h>
#include "sys_init.h"
#include "rx_tx_bus.h"

#define GSM_BUS           BUS_00_SELECT
#define GSM_CMD_TIMEOUT   2000

#define GSM_RX_BUFFER_SIZE 128

#define GSM_TURN_OFF_CELL       "AT+CFUN=0"
#define GSM_TURN_ON_RF          "AT+CFUN=1"
#define GSM_TURN_OFF_RF         "AT+CFUN=4"
#define GSM_SIM_STATUS          "AT+CPIN?"
#define GSM_GET_SIGNAL_STRENGTH "AT+CSQ"

bool gsmWriteAndValidateResponse(const char* command, const char* response);
int8_t gsmWrite(const char* command);
void gsmRead();
void gsmIsReady();
void gsmStopCommandEcho();
void gsmGetSIMStatus();
void gsmGetSignalStrength();
void gsmDisable();
void gsmEnableRadio();
void gsmEnableFlightMode();

#endif