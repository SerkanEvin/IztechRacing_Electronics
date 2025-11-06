#include <acc_functions.h>

TwoWire myWire(PB11, PB10); 

int ax, ay;
int axRaw, ayRaw, azRaw;


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

float convert_raw_gyro(int gRaw) {
  return (gRaw * 250.0) / 32768.0;
}