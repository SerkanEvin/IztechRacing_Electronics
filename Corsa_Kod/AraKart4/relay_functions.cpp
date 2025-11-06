#include <relay_functions.h>

const int relay = PA1;
uint8_t is_relay_on = 0;

void relay_control() { 
  if (msgRx.buf[1] == 1) {
    digitalWrite(relay, HIGH);
    is_relay_on = 1;
  } else if (msgRx.buf[1] == 0) {
    digitalWrite(relay, LOW);
    is_relay_on = 0;
  }
}

void relay_feedback() {
  if (is_relay_on == 1) {
    msgTx.buf[0] = 1;
  } else if (is_relay_on == 0) {
    msgTx.buf[0] = 0;
  }
}