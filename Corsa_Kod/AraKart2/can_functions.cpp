#include <can_functions.h>

STM32_CAN Can(PA_11, PA_12);
CAN_message_t msgRx;
CAN_message_t msgTx;

uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}

void begin_can() {
  Can.begin();
  Can.setBaudRate(250000);
  /*
  Can.setFilterDualID(0, make_j1939_id(4, 0xF350, 0x82), make_j1939_id(4, 0xF351, 0x82), EXT, EXT);
  Can.setFilterSingleMask(1, make_j1939_id(4, 0xF403, 0x83), 0x1FFFFFFF, EXT);
  Can.setFilterDualMask(2, make_j1939_id(6, 0xF100, 0x80), 0x1FFFFFFF, EXT, make_j1939_id(6, 0xF120, 0x82), 0x1FFFFFFF, EXT);
  Can.setFilterSingleMask(3, make_j1939_id(6, 0xF130, 0x83), 0x1FFFFFFF, EXT); */
  Can.setFilterSingleMask(0, 0, 0, EXT);

  msgRx.flags.extended = true;
  msgTx.flags.extended = true;
  msgTx.id = make_j1939_id(4, 0xF900, 0x81);
  msgTx.len = 8;
}


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
}

void is_kill_switch_on(){
  if(digitalRead(kill_switch_pin)==1){
    msgTx.buf[7] = 1;
  } else{
    msgTx.buf[7] = 0;
  }
}



void read_can_messages() {
  if (msgRx.id == make_j1939_id(4, 0xF700, 0x82)){
    send_engine_temp_to_screen();
  }
  if (msgRx.id == make_j1939_id(4, 0xF420, 0x83)) {
    send_speed_datas_to_screen();
  } else if (msgRx.id == make_j1939_id(3, 0xF350, 0x82)) {
    send_acc_datas_to_screen();
  } else if (msgRx.id == make_j1939_id(4, 0xF600, 0x80) || msgRx.id == make_j1939_id(4, 0xF700, 0x82) || msgRx.id == make_j1939_id(4, 0xF500, 0x83)) {
    send_kart_online_to_screen();
  }
}
