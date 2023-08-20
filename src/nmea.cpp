#include "nmea.h"
#include <stdio.h>

void NMEA::produceNMEA(char *buffer, const NMEA::timestamp& ts ){
  char payload[NMEA::BufferLen];
  // start time set to Sunday, September 13, 2020 12:26:40 PM - posix is 1600000000.
  const char date[] = "130920"; //dd/mm/yy  
  snprintf(payload, NMEA::BufferLen,
					"GPRMC,%02d%02d%02d.00,A,5109.0262308,N,11401.8407342,W,0.004,133.4,%s,0.0,E,D",
					ts.hours, ts.mins, ts.secs, date);
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
    