#ifndef CAN_FUNCTIONS_H
#define CAN_FUNCTIONS_H

#include <STM32_CAN.h>
#include <pin_management.h>
#include <screen_functions.h>

// can functions here
// begin
// sending button datas to can bus line and kill switch
// reading can bus line


extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);

extern STM32_CAN Can;
extern CAN_message_t msgRx;
extern CAN_message_t msgTx;


void begin_can();
void send_can_buttons();
void is_kill_switch_on();
void read_can_messages();

#endif