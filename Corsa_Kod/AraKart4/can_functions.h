#ifndef CAN_FUNCTIONS_H
#define CAN_FUNCTIONS_H

#include <STM32_CAN.h>
#include <stdint.h>

extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgTx;
extern CAN_message_t msgRx;

void can_begin();
void read_can_messages();
void send_can_messages();

//from other files begin
extern void relay_control();
extern void relay_feedback();
extern void gps_data();
//from other files end

#endif