#include "gps_management.h"
#include "can_functions.h"
#include "relay_functions.h"

// this one 
// has a brake light relay
// has a gps on it

unsigned long interval1 = 100;
unsigned long lastTime1 = 0;


void setup() {
  can_begin();
  GPS_Serial.begin(9600);
  pinMode(relay, OUTPUT);
}

void loop() {

  if (millis() - lastTime1 > interval1) {
    send_can_messages();
    lastTime1 = millis();
  }
  while (Can.read(msgRx)) {
    read_can_messages();
  }
}


