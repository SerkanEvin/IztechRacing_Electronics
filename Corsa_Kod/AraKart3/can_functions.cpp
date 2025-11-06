#include <can_functions.h>

STM32_CAN Can(CAN1, DEF);
uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}
CAN_message_t msgRx;
CAN_message_t msgTx;

void can_begin(){
  Can.begin();
  Can.setBaudRate(250000);
  Can.setFilterSingleMask(0, 0, 0, EXT);
  msgRx.flags.extended = true;
  msgTx.flags.extended = true;
}

void send_can_messages() {
  msgTx.id = make_j1939_id(4, 0xF700, 0x82);
  msgTx.len = 7;
  relay_feedback();  // engine cooler relay
  impact_data();
  msgTx.buf[2] = 1; // sent for feedback of arakart3 online
  engine_temp();
  Can.write(msgTx);
  delay(10);
  acceleration_data();
}

void read_can_messages() {
  if (msgRx.id == make_j1939_id(4, 0xF900, 0x81)) {
    relay_control();
  }
}