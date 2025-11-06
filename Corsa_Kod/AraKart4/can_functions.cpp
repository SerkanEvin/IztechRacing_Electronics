#include <can_functions.h>

STM32_CAN Can(PA_11, PA_12);
uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}
CAN_message_t msgTx;
CAN_message_t msgRx;

void can_begin(){
  Can.begin();
  Can.setBaudRate(250000);
  //Can.setFilterSingleMask(0, make_j1939_id(3, 0xF920, 0x81), 0x1FFFFFFF, EXT);
  Can.setFilterSingleMask(0, 0, 0, EXT);
  msgRx.flags.extended = true;
  msgTx.flags.extended = true;
}

void read_can_messages() {
  if (msgRx.id == make_j1939_id(4, 0xF600, 0x80)) {
    relay_control();
  }
}

void send_can_messages() {
  msgTx.id = make_j1939_id(4, 0xF500, 0x83);
  msgTx.len = 2;
  relay_feedback();
  msgTx.buf[1] = 1; // is kart4 online data
  Can.write(msgTx);
  delay(10);
  gps_data();
}