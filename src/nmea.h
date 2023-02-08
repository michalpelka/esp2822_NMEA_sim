#pragma once
#include <Arduino.h>
namespace NMEA{

    //! Max buffer len 
    const unsigned int BufferLen = 128;

    //! Helper structure to get time
    struct timestamp{
        uint8_t hours;
        uint8_t mins;
        uint8_t secs;
    };

    //! produce NMEA buffer.
    //! @param buffer pointer to buffer of size NMEABUFFFERLEN
    //! @param ts timestamp
    void produceNMEA(char *buffer, const timestamp& ts );


    timestamp GetTimestampFromSec(uint32_t secsElapsed);

}