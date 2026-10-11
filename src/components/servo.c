#include "components/servo.h"

#include <driver/ledc.h>

#define SERVO_PIN 23

ledc_timer_config_t ledc_timer = {
    .ledc_mode = LEDC_LOW_SPEED_MODE,
    .ledc_timer = LEDC_TIMER_0,
    .duty_resolution = LEDC_TIMER_8_BIT,
    .freq_hz = 50,
    .ledc_clk_cfg = LEDC_AUTO_CLK,
};
ledc_timer_config(&ledc_timer);


ledc_channel_config_t led_channel = {
    .gpio_num = SERVO_PIN,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_0,
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0,
};
ledc_channel_config(&led_channel);


void servo_move(){
    // moving the whole range of the servo from 0 to 180 degrees
    for(int duty = 0; duty <= 1023; duty += 10){
        ledc_set_duty(led_channel.speed_mode, led_channel.channel, duty);
        ledc_update_duty(led_channel.speed_mode, led_channel.channel);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}