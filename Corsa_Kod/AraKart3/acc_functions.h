#ifndef ACC_FUNCTIONS_H
#define ACC_FUNCTIONS_H

// for bmi160 usage
// bmi160 has its own wire lib from arduino 

// it does not work right now it should be fixed
// when bmi160 begin added can bus line crashes 
// should be looked how to use i2c2 with this bmi160 gen library

#include <BMI160Gen.h>
#include <STM32_CAN.h>
#include <stdint.h>



#define ACCEL_SENSITIVITY 16384.0  //±2g

extern int ax, ay;
extern int axRaw, ayRaw, azRaw;

extern TwoWire myWire; 

// from can_functions begin
extern STM32_CAN Can;
extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);
extern CAN_message_t msgRx;
extern CAN_message_t msgTx;
// from can_functions end

void acceleration_data();
void impact_data();
float convert_raw_gyro(int gRaw);


#endif