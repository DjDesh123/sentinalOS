#include "ultrasonicMaths.h"


static const char *TAG = "ultrasonic";


bool distance_check(float distance) {
    if (distance < 10.0f) {
        ESP_LOGI(TAG, "Obstacle detected at %.2f cm", distance);
        return true;
    } else {
        ESP_LOGI(TAG, "No obstacle detected. Distance: %.2f cm", distance);
        return false;
    }
}