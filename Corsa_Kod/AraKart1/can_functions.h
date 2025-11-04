#ifndef CAN_FUNCTIONS_H
#define CAN_FUNCTIONS_H

// this file is about just can bus begin and can bus
// can begin
// write brake case to can bus

#include <STM32_CAN.h>

#include <data_functions.h>

extern STM32_CAN Can;
extern CAN_message_t msgRx;
extern CAN_message_t msgTx;

extern const int brake_pin;

void can_begin();
void is_brake_on();

#endif