#ifndef CAN_FUNCTIONS_H
#define CAN_FUNCTIONS_H

#include <STM32_CAN.h>

#include <stdint.h>


extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgRx;
extern CAN_message_t msgTx;


void send_can_messages();
void read_can_messages();

// from other files begin
extern void relay_control();
extern void relay_feedback();
extern void engine_temp();
extern void acceleration_data();
extern void impact_data();
// from other files end

#endif