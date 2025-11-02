#include <STM32_CAN.h>
#include <BMI160Gen.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ACCEL_SENSITIVITY 16384.0  //±2g

//canbus
STM32_CAN Can(CAN1, DEF);
uint32_t make_j1939_id(uint8_t priority, uint16_t pgn, uint8_t sa) {
  return ((uint32_t)priority << 26) | ((uint32_t)pgn << 8) | sa;
}




const int relay = PA1;
int isRelay = 0;

const int engine_temp_pin = PB3;

OneWire oneWire(engine_temp_pin);
DallasTemperature ttl(&oneWire);

unsigned long interval1 = 250;
unsigned long lastTime1 = 0;

int ax, ay;
int axRaw, ayRaw, azRaw;

TwoWire myWire(PB11, PB10); 

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
// arakart3 icin --> 2 tane sicaklik sensoru, 1 tane ivme (carpisma) sensoru, 1 tane gps
// ivme sensorunde i2c kullaniliyor

// sıcaklık sensörü, gps, stop

// sogutucu role
// jigle servosu
// motor sicaklik
// bmi sensoru, carpisma durumu // parametreler sonrasinda hazir
CAN_message_t msgRx;
CAN_message_t msgTx;

void setup() {
  Can.begin();
  Can.setBaudRate(250000);
  Can.setFilterSingleMask(0, 0, 0, EXT);
  myWire.setSCL(PB10);
  myWire.setSDA(PB11);

  //BMI160.begin(BMI160GenClass::I2C_MODE, myWire);

  msgRx.flags.extended = true;
  msgTx.flags.extended = true;

  pinMode(relay, OUTPUT);

  ttl.begin();
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

void relay_feedback() {
  if (isRelay == 1) {
    msgTx.buf[0] = 1;
  } else if (isRelay == 0) {
    msgTx.buf[0] = 0;
  }
}

void acceleration_data() {
  //int gxRaw, gyRaw, gzRaw;
  //float gx, gy, gz;
  //BMI160.readGyro(gxRaw, gyRaw, gzRaw);
  BMI160.readAccelerometer(axRaw, ayRaw, azRaw);
  //gx = convertRawGyro(gxRaw);
  //gy = convertRawGyro(gyRaw);
  //gz = convertRawGyro(gzRaw);
  ax = axRaw * (9.81 / ACCEL_SENSITIVITY) * 5 + 5;
  ay = ayRaw * (9.81 / ACCEL_SENSITIVITY) * 5 + 5;  // bu sayede bari tam doldurabiliriz
  msgTx.id = make_j1939_id(3, 0xF350, 0x82);  // ax and ay values are sent by this id
  msgTx.len = 8;
  memcpy(msgTx.buf, &ax, sizeof(int));                // they are in the same message since there are 8 bytes of data allowed
  memcpy(msgTx.buf + sizeof(int), &ay, sizeof(int));  // diger kartta bunun acilmasi yapilacak
  Can.write(msgTx);
  delay(5);
}

void impact_data() {
  //double gForce;
  //parametrelere bakilip kosullar olusturulacak
  if (/*carpisma gerceklesmisse*/ 0) {
    msgTx.buf[1] = 1;
  } else if (1) {
    msgTx.buf[1] = 0;
  }
}


void is_kart3_online() {
  msgTx.buf[2] = 1;
}

void relay_control() {
  if (msgRx.buf[2] == 1) {  // switch left
    digitalWrite(relay, HIGH);
    isRelay = 1;
  } else if (msgRx.buf[2] == 0) {
    digitalWrite(relay, LOW);
    isRelay = 0;
  }
}

void engine_temp(){
  ttl.requestTemperatures(); 
  float temp = ttl.getTempCByIndex(0);
  int temp_int = int(temp);
  memcpy(msgTx.buf + 3, &temp_int, sizeof(int));
}

float convert_raw_gyro(int gRaw) {
  return (gRaw * 250.0) / 32768.0;
}

void read_can_messages() {
  if (msgRx.id == make_j1939_id(4, 0xF900, 0x81)) {
    relay_control();
  }
}

void send_can_messages() {
  msgTx.id = make_j1939_id(4, 0xF700, 0x82);
  msgTx.len = 7;
  relay_feedback();  // engine cooler relay
  impact_data();
  is_kart3_online();
  engine_temp();
  Can.write(msgTx);
  delay(10);
  acceleration_data();
}