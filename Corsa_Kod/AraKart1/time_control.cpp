#include <time_control.h>

// waiting times are declared in here
unsigned long interval1 = 50; // this changed to 50 from 150 to see if there is effective delay here
unsigned long lastTime1 = 0;
unsigned long interval2 = 250;
unsigned long lastTime2 = 0;
unsigned long kart_controls_interval = 3000;
unsigned long kart_controls_time = 0;
// time declaration end