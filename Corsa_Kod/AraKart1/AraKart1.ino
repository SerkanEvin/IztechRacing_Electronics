#include <raspberry_functions.h>
#include <time_control.h>

const int brake_pin = PA7;

void setup() {
  can_begin();

  pinMode(brake_pin, INPUT_PULLUP);

  Serial1.begin(9600);
}

void loop() {
  if (millis() - lastTime1 > interval1) {
    is_brake_on();
    Can.write(msgTx);
    lastTime1 = millis();
  }
  if (millis() - lastTime2 > interval2) {
    send_datas_to_raspberry();
    lastTime2 = millis();
  }
  while (Can.read(msgRx)) {
    put_can_datas_to_array();  // as there are can messages it reads and gets all the datas from other kart's
  }
}
