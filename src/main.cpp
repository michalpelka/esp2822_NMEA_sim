#include <Arduino.h>
#include "ESP8266TimerInterrupt.h"
#include "nmea.h"

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default
#define TIMER_FREQ_HZ       10
// Init ESP8266 timer 1
ESP8266Timer ITimer;
const byte PpsPin = D1;

static bool led_state = true; 
static uint64_t count =0;
static uint32_t elapsedSecs =0;


char bufferNmea[NMEA::BufferLen];
struct timestamp{
  uint8_t hours;
  uint8_t mins;
  uint8_t secs;
};

void IRAM_ATTR TimerHandler()
{
  digitalWrite(LED_BUILTIN, led_state);

  if (count%10 == 0){
    elapsedSecs++;
    digitalWrite(PpsPin, true);
    NMEA::timestamp ts = NMEA::GetTimestampFromSec(elapsedSecs);
    NMEA::produceNMEA(bufferNmea, ts);
  }
  else{
    if (count%10 ==5){
      Serial.print(bufferNmea);
    }
    digitalWrite(PpsPin, false);
  }

  led_state = !led_state;
  count++;
}
void setup()
{
 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PpsPin, OUTPUT);
  
  Serial.print(F("\nPPS ticking!\n"));
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP8266_TIMER_INTERRUPT_VERSION);
  Serial.begin(9600);
  // Frequency in float Hz
  if (ITimer.attachInterrupt(TIMER_FREQ_HZ, TimerHandler))
    Serial.println("Starting  ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");
}  


void loop()
{
  delay(900);
}