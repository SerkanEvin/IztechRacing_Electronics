#ifndef ENGINE_TEMP_H
#define ENGINE_TEMP_H

// here we use temp sensor
// with onewire lib since it works with one wire thing

#include <DallasTemperature.h>
#include <OneWire.h>

#include <STM32_CAN.h>
#include <stdint.h>

extern const int engine_temp_pin;

// from can_functions begin
extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgRx;
extern CAN_message_t msgTx;
// from can_functions end

extern OneWire oneWire;
extern DallasTemperature ttl;

void engine_temp();

#endif