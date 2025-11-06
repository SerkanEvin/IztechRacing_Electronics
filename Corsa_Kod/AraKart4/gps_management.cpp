#include <gps_management.h>

NMEAGPS gps;
gps_fix fix;
HardwareSerial GPS_Serial(USART1);


void gps_data() {
  if (gps.available(GPS_Serial)) {
    fix = gps.read();
    
    if (fix.valid.location) {
      int latitude = fix.latitude() * 1000000;
      int longitude = fix.longitude() * 1000000; // karşı taraflarda da bir milyon ile bölünmesi lazım

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