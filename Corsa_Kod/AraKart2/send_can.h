

void send_can_buttons() {
  if (digitalRead(butonLeft) == 1) {  // bozuk
    msgTx.buf[0] = 1;
  } else {
    msgTx.buf[0] = 0;
  }
  if (digitalRead(butonRight) == 1) {  //calisiyor
    msgTx.buf[1] = 1;
  } else {
    msgTx.buf[1] = 0;
  }
  if (digitalRead(switchLeft) == 1) {  //  calisiyor
    msgTx.buf[2] = 1;
  } else {
    msgTx.buf[2] = 0;
  }
  if (digitalRead(switchLeftRight) == 1) {  //calisiyor
    msgTx.buf[3] = 1;
  } else {
    msgTx.buf[3] = 0;
  }
  if (digitalRead(switchRight) == 1) {  //calismiyor
    msgTx.buf[4] = 1;
  } else {
    msgTx.buf[4] = 0;
  }
  if (digitalRead(switchRightLeft) == 1) {  //calisiyor
    msgTx.buf[5] = 1;
  } else {
    msgTx.buf[5] = 0;
  }
  msgTx.buf[6] = 1;  // sent to kart1 to tell that kart2 is on
  Can.write(msgTx);
}