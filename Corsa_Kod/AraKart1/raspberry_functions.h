#ifndef RASPBERRY_FUNCTIONS_H
#define RASPBERRY_FUNCTIONS_H

// this file includes 
// sending datas to raspberry as json
// taking datas from canbus 

#include <Arduino.h>
#include <ArduinoJson.h>

#include "can_functions.h"

extern unsigned long kart_controls_interval;
extern unsigned long kart_controls_time;

void send_datas_to_raspberry();

void put_can_datas_to_array();

#endif