#include "raspberry_functions.h"

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
  if (millis() - kart_controls_time > kart_controls_interval) {
    doc["idx_kart2_control"] = 0;
    doc["idx_kart3_control"] = 0;
    doc["idx_kart4_control"] = 0;
    kart_controls_time = millis();
  }
}


void put_can_datas_to_array() {  //for rasp pi

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