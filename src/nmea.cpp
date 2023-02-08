#include "nmea.h"
#include <stdio.h>

void NMEA::produceNMEA(char *buffer, const NMEA::timestamp& ts ){
  char payload[NMEA::BufferLen];
  snprintf(payload, NMEA::BufferLen,
					"GPRMC,%02d%02d%02d,A,10.00,N,10.00,E,001.5,312.2,010100,005.3,E,A",
					ts.hours, ts.mins, ts.secs);
    size_t len = strnlen(payload, NMEA::BufferLen);
    // compute NMEA checksum on buffer
    uint8_t NMEAChecksumComputed = 0;

    size_t i = 0;
    for (i = 0; i < len; i++) {
      NMEAChecksumComputed ^=  payload[i];
    }
    // attach cheksum
    snprintf(buffer, NMEA::BufferLen, "$%s*%02X\n", payload, NMEAChecksumComputed);
}

NMEA::timestamp NMEA::GetTimestampFromSec(uint32_t secsElapsed){
    NMEA::timestamp ts;
    ts.hours = secsElapsed / 3600;
    ts.mins  = (secsElapsed % 3600) / 60;
    ts.secs = secsElapsed%60;
    return ts;
}
    