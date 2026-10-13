#include "include/components/ultrasonic/ultrasonic.h"
#include "hal/gpio_types.h"

#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_timer.h>


#define TRIG_PIN 33
#define ECHO_PIN 25

static const char *TAG = "ultrasonic";

static void clean_signal();
static bool distance_check(float distance);

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

bool detect_obstacle() {

    // starts with a clean signal
    clean_signal();
    
    int64_t start_time = esp_timer_get_time();

    //sends a 10 microseocn pulse to trigger the sensor
    gpio_set_level(TRIG_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(TRIG_PIN, 0);


    while(gpio_get_level(ECHO_PIN) == 0) {
        if(esp_timer_get_time() - start_time > 1000000) { // 1 second timeout
            ESP_LOGE(TAG, "Timeout waiting for ECHO pin to go high");
            return false;
        }
    }

    int64_t echo_start = esp_timer_get_time();

    while(gpio_get_level(ECHO_PIN) == 1) {
        if(esp_timer_get_time() - echo_start > 1000000) { // 1 second timeout
            ESP_LOGE(TAG, "Timeout waiting for ECHO pin to go low");
            return false;
        }
    }

    int64_t pulse_duration = esp_timer_get_time() - echo_start;
    float distance = (pulse_duration / 2.0) * 0.0343f;

    bool obstacle_detected = distance_check(distance);
    return obstacle_detected;
}


static void clean_signal() {
    gpio_set_level(TRIG_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(2));
}


static bool distance_check(float distance) {
    if (distance < 10.0f) {
        ESP_LOGI(TAG, "Obstacle detected at %.2f cm", distance);
        return true;
    } else {
        ESP_LOGI(TAG, "No obstacle detected. Distance: %.2f cm", distance);
        return false;
    }
}