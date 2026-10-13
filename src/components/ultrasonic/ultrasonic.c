#include "include/components/ultrasonic/ultrasonic.h"

#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_log.h>

#define TRIG_PIN 33
#define ECHO_PIN 25

static const char *TAG = "ultrasonic";

bool ultrasonic_init() {
    // Initialize the ultrasonic sensor here
    esp_err_t gpio_config_trig = gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
    esp_err_t gpio_config_echo = gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);

    if (gpio_config_trig != ESP_OK || gpio_config_echo != ESP_OK) {
        ESP_LOGE(TAG, "Error configuring GPIO pins for ultrasonic sensor");
        return false;
    }
    return true;
}

