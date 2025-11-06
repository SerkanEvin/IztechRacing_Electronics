#include <screen_functions.h>


void send_speed_datas_to_screen() {
  int speed;
  memcpy(&speed, msgRx.buf, sizeof(int));
  Serial1.print(F("speed.val="));
  Serial1.print(speed);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
}


void send_acc_datas_to_screen() {
  int ax, ay;
  memcpy(&ax, msgRx.buf, sizeof(int));
  memcpy(&ay, msgRx.buf + sizeof(int), sizeof(int));
  Serial1.print(F("j0.val="));
  Serial1.print(ax);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.print(F("j1.val="));
  Serial1.print(ay);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
}


void send_kart_online_to_screen() {
  if (msgRx.id == make_j1939_id(4, 0xF600, 0x80) && msgRx.buf[0] == 1) {
    Serial1.print(F("b0.bco="));
    Serial1.print("22033");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  } else if (msgRx.id == make_j1939_id(4, 0xF700, 0x82) && msgRx.buf[2] == 1) {
    Serial1.print(F("b2.bco="));
    Serial1.print("22033");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  } else if (msgRx.id == make_j1939_id(4, 0xF500, 0x83) && msgRx.buf[1] == 1) {
    Serial1.print(F("b3.bco="));
    Serial1.print("22033");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
}


void send_engine_temp_to_screen(){
    int temp;
    memcpy(&temp, msgRx.buf + 3, sizeof(int));
    Serial1.print(F("n0.val="));
    Serial1.print(temp);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
}

