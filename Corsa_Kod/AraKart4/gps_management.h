#ifndef GPS_MANAGEMENT_H
#define GPS_MANAGEMENT_H

// it is to control gps

#include <NMEAGPS.h>
#include <STM32_CAN.h>



extern NMEAGPS gps;
extern gps_fix fix;
extern HardwareSerial GPS_Serial;

// from other files begin
extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgTx;
extern CAN_message_t msgRx;
// from other files end

void gps_data();

#endif