#include <pin_management.h>

const int butonLeft = PA3;
const int butonRight = PA6;
const int switchLeft = PB9;
const int switchLeftRight = PA2;
const int switchRight = PB5;
const int switchRightLeft = PB8;
const int kill_switch_pin = PB14;

void pin_mode(){
  pinMode(butonLeft, INPUT_PULLUP);
  pinMode(butonRight, INPUT_PULLUP);
  pinMode(switchLeft, INPUT_PULLUP);
  pinMode(switchLeftRight, INPUT_PULLUP);
  pinMode(switchRight, INPUT_PULLUP);
  pinMode(switchRightLeft, INPUT_PULLUP);
  pinMode(kill_switch_pin, INPUT_PULLUP);
}