#ifndef SCREEN_FUNCTIONS_H
#define SCREEN_FUNCTIONS_H

#include <can_functions.h>

// this file communicates with the screen
// sends speed datas which comes from gps
// sends acc datas which comes from bmi160
// sends temp data which comes from engine temperature sensor

void send_speed_datas_to_screen();
void send_acc_datas_to_screen();
void send_kart_online_to_screen();
void send_engine_temp_to_screen();

#endif