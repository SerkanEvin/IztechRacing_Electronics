#include <STM32_CAN.h>
#include <NMEAGPS.h>

//canbus
STM32_CAN Can(PA_11, PA_12);
uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}

const int relay = PA1;
uint8_t is_relay_on = 0;

NMEAGPS gps;
gps_fix fix;
HardwareSerial GPS_Serial(USART1);

unsigned long interval1 = 100;
unsigned long lastTime1 = 0;


/*
Servo1 PB0
Servo2 PB1
CANTX1 PA12
CANRX1 PA11
gps için TX1 RX1  PA9 PA10
ivme için SCL2 SDA2 PB10 PB11
sıcaklık için SCL1 SDA1 PB6 PB7
röle için PA1
*/

// gps burada olacak
// stop ledi burada olacak

CAN_message_t msgTx;
CAN_message_t msgRx;

void setup() {
  Can.begin();
  Can.setBaudRate(250000);
  //Can.setFilterSingleMask(0, make_j1939_id(3, 0xF920, 0x81), 0x1FFFFFFF, EXT);
  Can.setFilterSingleMask(0, 0, 0, EXT);

  GPS_Serial.begin(9600);

  msgRx.flags.extended = true;
  msgTx.flags.extended = true;

  pinMode(relay, OUTPUT);
}

void loop() {

  if (millis() - lastTime1 > interval1) {
    send_can_messages();
    lastTime1 = millis();
  }
  while (Can.read(msgRx)) {
    read_can_messages();
  }
}


void relay_control() { 
  if (msgRx.buf[1] == 1) {
    digitalWrite(relay, HIGH);
    is_relay_on = 1;
  } else if (msgRx.buf[1] == 0) {
    digitalWrite(relay, LOW);
    is_relay_on = 0;
  }
}


void relay_feedback() {
  if (is_relay_on == 1) {
    msgTx.buf[0] = 1;
  } else if (is_relay_on == 0) {
    msgTx.buf[0] = 0;
  }
}

void gps_data() {
  if (gps.available(GPS_Serial)) {
    fix = gps.read();
    
    if (fix.valid.location) {
      int latitude = fix.latitude() * 1000000;
      int longitude = fix.longitude() * 1000000; // karşı taraflarda bir milyon ile bölünmesi lazım

      msgTx.id = make_j1939_id(4, 0xF400, 0x83);
      msgTx.len = 8;
      memcpy(msgTx.buf, &latitude, sizeof(int));
      memcpy(msgTx.buf + sizeof(int), &longitude, sizeof(int));
      Can.write(msgTx);
      delay(10);
    }
    /*
    if (fix.valid.altitude) {
      int altitude = fix.altitude() * 1000000 ;
      msgTx.id=make_j1939_id(4, 0xF410, 0x83);
      msgTx.len = 4;
      memcpy(msgTx.buf, &altitude, sizeof(int));
      Can.write(msgTx);
      delay(10); 
    } */

    if (fix.valid.date && fix.valid.time && fix.valid.speed) {
      int speed = fix.speed_kph();
      msgTx.id = make_j1939_id(4, 0xF420, 0x83);
      msgTx.len = 7;
      memcpy(msgTx.buf, &speed, sizeof(int));
      msgTx.buf[4] = fix.dateTime.hours;
      msgTx.buf[5] = fix.dateTime.minutes;
      msgTx.buf[6] = fix.dateTime.seconds;
      Can.write(msgTx);
    }
  }
}


void is_kart4_online() {
  msgTx.buf[1] = 1;
}


void read_can_messages() {
  if (msgRx.id == make_j1939_id(4, 0xF600, 0x80)) {
    relay_control();
  }
}

void send_can_messages() {
  msgTx.id = make_j1939_id(4, 0xF500, 0x83);
  msgTx.len = 2;
  relay_feedback();
  is_kart4_online();
  Can.write(msgTx);
  delay(10);
  gps_data();
}
