#include <screen_functions.h>

// that one 
// communicates with the screen
// gets data from buttons
// gets data from kill switch also

unsigned long interval1 = 200;
unsigned long lastTime1 = 0;
// no need to create another file for now, for time management

void setup() {
  pin_mode();
  Serial1.begin(9600);
  begin_can();
}

void loop() {
  if (millis() - lastTime1 > interval1) {
    send_can_buttons();
    is_kill_switch_on();
    Can.write(msgTx);

    Serial1.print(F("b1.bco="));  // this part sends data to the screen to tell kart2 is connected
    Serial1.print("22033");
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);

    lastTime1 = millis();
  }
  while (Can.read(msgRx)) {
    read_can_messages();
  }
}


