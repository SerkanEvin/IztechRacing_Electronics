#ifndef RELAY_FUNCTIONS_H
#define RELAY_FUNCTIONS_H

// brake light control and feedback

#include <STM32_CAN.h>

extern const int relay;
extern uint8_t is_relay_on;

// from other files begin
extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgTx;
extern CAN_message_t msgRx;
// from other files end

#endif