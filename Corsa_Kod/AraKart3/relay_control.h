#ifndef RELAY_CONTROL_H
#define RELAY_CONTROL_H

#include <STM32_CAN.h>
#include <stdint.h>


extern const int relay;
extern int isRelay;

// from can_functions begin
extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgRx;
extern CAN_message_t msgTx;
// from can_functions end


void relay_control();
void relay_feedback();

#endif