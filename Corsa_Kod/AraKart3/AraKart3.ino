#include "can_functions.h"
#include "relay_control.h"
#include "engine_temp.h"
#include "acc_functions.h"

// this one
// has bmi160, acc sensor
// engine temp sensor

unsigned long interval1 = 250;
unsigned long lastTime1 = 0;
// no need to create file for time management

void setup() {
  pinMode(relay, OUTPUT);
  ttl.begin();
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

