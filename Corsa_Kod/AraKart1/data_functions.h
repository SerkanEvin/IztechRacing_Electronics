#ifndef DATA_FUNCTIONS_H
#define DATA_FUNCTIONS_H

// data funcitons include declarations
// enum for an array
// array to send datas to raspberry
// declaration of j1939 id's
#include <stdint.h>

extern uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa);

#define SENSOR_COUNT 26
#define TEXT_BUFFER_SIZE 300

extern int sensorData[SENSOR_COUNT];

enum SensorIndex {
  IDX_GX,
  IDX_GY,
  IDX_GZ,
  IDX_AX,
  IDX_AY,
  IDX_AZ,
  IDX_LAT,
  IDX_LON,
  IDX_ALT,
  IDX_SPD,
  IDX_IMPACT,
  IDX_HOUR,
  IDX_MIN,
  IDX_SEC,
  IDX_STOPLIGHT,
  IDX_LOG_BUTTON,
  IDX_BUTON1,
  IDX_BUTON2,
  IDX_SWITCH1,
  IDX_SWITCH2,
  IDX_SWITCH3,
  IDX_SWITCH4,
  IDX_KART2_CONTROL,
  IDX_KART3_CONTROL,
  IDX_KART4_CONTROL,
  IDX_KILL_SWITCH
};


extern uint32_t ID_GX;
extern uint32_t ID_GY;
extern uint32_t ID_GZ;
extern uint32_t ID_AX;
extern uint32_t ID_AY;
extern uint32_t ID_AZ;
extern uint32_t ID_IMPACT;
extern uint32_t ID_LAT;
extern uint32_t ID_LON;
extern uint32_t ID_ALT;
extern uint32_t ID_SPD;
extern uint32_t ID_HOUR;
extern uint32_t ID_MIN;
extern uint32_t ID_SEC;
extern uint32_t ID_STOP;
extern uint32_t ID_LOG_BUTTON;
extern uint32_t ID_BUTON1;
extern uint32_t ID_BUTON2;
extern uint32_t ID_SWITCH1;
extern uint32_t ID_SWITCH2;
extern uint32_t ID_SWITCH3;
extern uint32_t ID_SWITCH4;
extern uint32_t ID_KILL_SWITCH;
extern uint32_t ID_KART2_CONTROL;
extern uint32_t ID_KART3_CONTROL;
extern uint32_t ID_KART4_CONTROL;


#endif