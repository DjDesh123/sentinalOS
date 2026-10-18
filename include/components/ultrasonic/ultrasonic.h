#ifndef ULTRASONIC_H
#define ULTRASONIC_H


#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "hal/gpio_types.h"

void ultrasonic_init();
bool detect_obstacle();


#endif // ULTRASONIC_H