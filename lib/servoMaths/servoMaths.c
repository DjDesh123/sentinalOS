#include "servoMaths.h"


int angle_to_duty(int angle) {
    int pulse_width = 500 + (angle * 2000 / 180); 
    int duty = (pulse_width * 1023) / 20000;
    return duty;
}