#include <engine_temp.h>

const int engine_temp_pin = PB3;

OneWire oneWire(engine_temp_pin);
DallasTemperature ttl(&oneWire);

void engine_temp(){
  ttl.requestTemperatures(); 
  float temp = ttl.getTempCByIndex(0);
  int temp_int = int(temp);
  memcpy(msgTx.buf + 3, &temp_int, sizeof(int));
}