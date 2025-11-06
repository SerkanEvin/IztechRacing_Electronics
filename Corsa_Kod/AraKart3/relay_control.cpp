#include <relay_control.h>

const int relay = PA1;
int isRelay = 0;

void relay_control() {
  if (msgRx.buf[2] == 1) {
    digitalWrite(relay, HIGH);
    isRelay = 1;
  } else if (msgRx.buf[2] == 0) {
    digitalWrite(relay, LOW);
    isRelay = 0;
  }
}

void relay_feedback() {
  if (isRelay == 1) {
    msgTx.buf[0] = 1;
  } else if (isRelay == 0) {
    msgTx.buf[0] = 0;
  }
}