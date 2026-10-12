#include "components/servo/servoMaths.h"


int angle_to_duty(int angle) {
    int pulse_width = 500 + (angle * 2000 / 180); // Convert angle to pulse width (500-2500us)
    int duty = (pulse_width * 1023) / 20000; // Convert pulse width to duty cycle (0-1023)
    return duty;
}