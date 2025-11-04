#include <can_functions.h>


STM32_CAN Can(PA_11, PA_12);
CAN_message_t msgRx;
CAN_message_t msgTx;

void can_begin(){
  Can.begin();
  Can.setBaudRate(250000);
  Can.setFilterSingleMask(0, 0, 0, EXT);

  msgTx.flags.extended = true;
  msgRx.flags.extended = true;
  msgTx.len = 2;
  msgTx.id = make_j1939_id(4, 0xF600, 0x80);
  msgTx.buf[0] = 1;
}

void is_brake_on(){
  if(digitalRead(brake_pin)==1){
    msgTx.buf[1] = 0;
  } else{
    msgTx.buf[1] = 1;
  }
}