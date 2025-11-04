#include "data_functions.h"

uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}

int sensorData[SENSOR_COUNT];

// all can j1939 id's here for this kart
uint32_t ID_GX = make_j1939_id(3, 0xF340, 0x82);
uint32_t ID_GY = make_j1939_id(3, 0xF341, 0x82);
uint32_t ID_GZ = make_j1939_id(3, 0xF342, 0x82);
uint32_t ID_AX = make_j1939_id(3, 0xF350, 0x82);
uint32_t ID_AY = make_j1939_id(3, 0xF350, 0x82);
uint32_t ID_AZ = make_j1939_id(3, 0xF352, 0x82);
uint32_t ID_IMPACT = make_j1939_id(4, 0xF700, 0x82);
uint32_t ID_LAT = make_j1939_id(4, 0xF400, 0x83);
uint32_t ID_LON = make_j1939_id(4, 0xF400, 0x83);
uint32_t ID_ALT = make_j1939_id(4, 0xF410, 0x83);
uint32_t ID_SPD = make_j1939_id(4, 0xF420, 0x83);
uint32_t ID_HOUR = make_j1939_id(4, 0xF420, 0x83);
uint32_t ID_MIN = make_j1939_id(4, 0xF420, 0x83);
uint32_t ID_SEC = make_j1939_id(4, 0xF420, 0x83);
uint32_t ID_STOP = make_j1939_id(4, 0xF500, 0x83);
uint32_t ID_LOG_BUTTON = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_BUTON1 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_BUTON2 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH1 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH2 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH3 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH4 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_KILL_SWITCH = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_KART2_CONTROL = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_KART3_CONTROL = make_j1939_id(4, 0xF700, 0x82);
uint32_t ID_KART4_CONTROL = make_j1939_id(4, 0xF500, 0x83);