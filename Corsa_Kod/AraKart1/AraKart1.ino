#include <STM32_CAN.h>
#include <Wire.h>
#include <ArduinoJson.h>


//sadece raspi var


#define SENSOR_COUNT 26
#define TEXT_BUFFER_SIZE 300

int sensorData[SENSOR_COUNT];


unsigned long interval1 = 150;
unsigned long lastTime1 = 0;
unsigned long interval2 = 500;
unsigned long lastTime2 = 0;
unsigned long interval3 = 3000;
unsigned long lastTime3 = 0;

const int brake_pin = PA7;


//canbus
STM32_CAN Can(PA_11, PA_12);
uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}

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

// declaration id's
uint32_t ID_GX = make_j1939_id(3, 0xF340, 0x82);
uint32_t ID_GY = make_j1939_id(3, 0xF341, 0x82);
uint32_t ID_GZ = make_j1939_id(3, 0xF342, 0x82);  // gyro datas are not avaliable now
uint32_t ID_AX = make_j1939_id(3, 0xF350, 0x82);  // first 4
uint32_t ID_AY = make_j1939_id(3, 0xF350, 0x82);  // second 4
uint32_t ID_AZ = make_j1939_id(3, 0xF352, 0x82);  // az is not avaliable now
uint32_t ID_IMPACT = make_j1939_id(4, 0xF700, 0x82);
uint32_t ID_LAT = make_j1939_id(4, 0xF400, 0x83);
uint32_t ID_LON = make_j1939_id(4, 0xF400, 0x83);
uint32_t ID_ALT = make_j1939_id(4, 0xF410, 0x83);   // altitude is no avaliable now
uint32_t ID_SPD = make_j1939_id(4, 0xF420, 0x83);   // first 4
uint32_t ID_HOUR = make_j1939_id(4, 0xF420, 0x83);  // 5th
uint32_t ID_MIN = make_j1939_id(4, 0xF420, 0x83);   // 6th
uint32_t ID_SEC = make_j1939_id(4, 0xF420, 0x83);   // 7th after speed value
uint32_t ID_STOP = make_j1939_id(4, 0xF500, 0x83);
uint32_t ID_LOG_BUTTON = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_BUTON1 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_BUTON2 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH1 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH2 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH3 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_SWITCH4 = make_j1939_id(4, 0xF900, 0x81);
uint32_t ID_KILL_SWITCH = make_j1939_id(4, 0xF900, 0x81);
//uint32_t ID_KART1_CONTROL = make_j1939_id(4, 0xF100, 0x80); [0]
uint32_t ID_KART2_CONTROL = make_j1939_id(4, 0xF900, 0x81); // [6]
uint32_t ID_KART3_CONTROL = make_j1939_id(4, 0xF700, 0x82); // [2]
uint32_t ID_KART4_CONTROL = make_j1939_id(4, 0xF500, 0x83); // [1]

CAN_message_t msgRx;
CAN_message_t msgTx;


void setup() {

  Can.begin();
  Can.setBaudRate(250000);
  Can.setFilterSingleMask(0, 0, 0, EXT);

  pinMode(brake_pin, INPUT_PULLUP);

  msgTx.flags.extended = true;
  msgRx.flags.extended = true;
  msgTx.len = 2;
  msgTx.id = make_j1939_id(4, 0xF600, 0x80);
  msgTx.buf[0] = 1;

  Serial1.begin(9600);
}

void loop() {
  if (millis() - lastTime1 > interval1) {
    is_brake_on();
    Can.write(msgTx);
    lastTime1 = millis();
  }
  if (millis() - lastTime2 > interval2) {
    send_datas_to_raspberry();
    lastTime2 = millis();
  }
  while (Can.read(msgRx)) {
    get_can_datas();  // as there are can messages it reads and gets all the datas from other kart's
  }
}

void get_can_datas() {  //for rasp pi

  // taking values by controlling can id's
  if (msgRx.id == ID_GX) {
    memcpy(&sensorData[IDX_GX], msgRx.buf, sizeof(int));
  } else if (msgRx.id == ID_GY) {
    memcpy(&sensorData[IDX_GY], msgRx.buf, sizeof(int));
  } else if (msgRx.id == ID_GZ) {
    memcpy(&sensorData[IDX_GZ], msgRx.buf, sizeof(int)); // gyro is not in use now
  } else if (msgRx.id == ID_AX) {
    memcpy(&sensorData[IDX_AX], msgRx.buf, sizeof(int));
    sensorData[IDX_AX] = (sensorData[IDX_AX] - 5) / 5;
    memcpy(&sensorData[IDX_AY], msgRx.buf + sizeof(int), sizeof(int));
    sensorData[IDX_AY] = (sensorData[IDX_AY] - 5) / 5;
  } else if (msgRx.id == ID_AZ) { // not in use now
    memcpy(&sensorData[IDX_AZ], msgRx.buf, sizeof(int));
  } else if (msgRx.id == ID_LAT) {
    memcpy(&sensorData[IDX_LAT], msgRx.buf, sizeof(int));
    memcpy(&sensorData[IDX_LON], msgRx.buf + sizeof(int), sizeof(int));
  } else if (msgRx.id == ID_ALT) { // not in use now
    memcpy(&sensorData[IDX_ALT], msgRx.buf, sizeof(int));
  } else if (msgRx.id == ID_SPD) {
    memcpy(&sensorData[IDX_SPD], msgRx.buf, sizeof(int));
    sensorData[IDX_HOUR] = int(msgRx.buf[4]);
    sensorData[IDX_MIN] = int(msgRx.buf[5]);
    sensorData[IDX_SEC] = int(msgRx.buf[6]);
  } else if (msgRx.id == ID_KART2_CONTROL) { 
    sensorData[IDX_KART2_CONTROL] = int(msgRx.buf[6]);
    sensorData[IDX_LOG_BUTTON] = int(msgRx.buf[1]);
    sensorData[IDX_BUTON1] = int(msgRx.buf[0]);
    sensorData[IDX_BUTON2] = int(msgRx.buf[1]);
    sensorData[IDX_SWITCH1] = int(msgRx.buf[2]);
    sensorData[IDX_SWITCH2] = int(msgRx.buf[3]);
    sensorData[IDX_SWITCH3] = int(msgRx.buf[4]);
    sensorData[IDX_SWITCH4] = int(msgRx.buf[5]);
    sensorData[IDX_KILL_SWITCH] = int(msgRx.buf[7]);
  } else if (msgRx.id == ID_KART3_CONTROL) {
    sensorData[IDX_KART3_CONTROL] = int(msgRx.buf[2]);
    sensorData[IDX_IMPACT] = int(msgRx.buf[1]);
  } else if (msgRx.id == ID_KART4_CONTROL) {
    sensorData[IDX_KART4_CONTROL] = int(msgRx.buf[1]);
    sensorData[IDX_STOPLIGHT] = int(msgRx.buf[0]);
  }
}

void send_datas_to_raspberry() {

  JsonDocument doc;
  doc["idx_gx"] = sensorData[IDX_GX];
  doc["idx_gy"] = sensorData[IDX_GY];
  doc["idx_gz"] = sensorData[IDX_GZ];
  doc["idx_ax"] = sensorData[IDX_AX];
  doc["idx_ay"] = sensorData[IDX_AY];
  doc["idx_az"] = sensorData[IDX_AZ];
  doc["idx_lat"] = sensorData[IDX_LAT];
  doc["idx_lon"] = sensorData[IDX_LON];
  doc["idx_alt"] = sensorData[IDX_ALT];
  doc["idx_spd"] = sensorData[IDX_SPD];
  doc["idx_impact"] = sensorData[IDX_IMPACT];
  doc["idx_hour"] = sensorData[IDX_HOUR];
  doc["idx_min"] = sensorData[IDX_MIN];
  doc["idx_sec"] = sensorData[IDX_SEC];
  doc["idx_stoplight"] = sensorData[IDX_STOPLIGHT];
  doc["idx_log_button"] = sensorData[IDX_LOG_BUTTON];

  doc["idx_button1_control"] = sensorData[IDX_BUTON1]; // 
  doc["idx_button2_control"] = sensorData[IDX_BUTON2];
  doc["idx_swi1_control"] = sensorData[IDX_SWITCH1];
  doc["idx_swi2_control"] = sensorData[IDX_SWITCH2];
  doc["idx_swi3_control"] = sensorData[IDX_SWITCH3];
  doc["idx_swi4_control"] = sensorData[IDX_SWITCH4];
  doc["idx_kswi_control"] = sensorData[IDX_KILL_SWITCH];


  //doc["idx_kart1_control"] = sensorData[IDX_KART1_CONTROL]; json veri aliyorsa kart1 aciktir
  doc["idx_kart2_control"] = sensorData[IDX_KART2_CONTROL];
  doc["idx_kart3_control"] = sensorData[IDX_KART3_CONTROL];
  doc["idx_kart4_control"] = sensorData[IDX_KART4_CONTROL];

  serializeJson(doc, Serial1);
  Serial.println();
  // burada durumlarini sifirliyoruz
  // buradakilerin 0'lanma surelerini bir sure gectikten sonra yapmaliyiz
  if (millis() - lastTime3 > interval3) {
    doc["idx_kart2_control"] = 0;
    doc["idx_kart3_control"] = 0;
    doc["idx_kart4_control"] = 0;
    lastTime3 = millis();
  }
}


void is_brake_on(){
  if(digitalRead(brake_pin)==1){
    msgTx.buf[1] = 0;
  } else{
    msgTx.buf[1] = 1;
  }
}
