#include "components/servo.h"

#include <driver/ledc.h>
#include <freertos/FreeRTOS.h>

#define SERVO_PIN 18



static void reset_servo(ledc_timer_config_t timer_config, ledc_channel_config_t led_channel);
void servo_move(ledc_timer_config_t timer_config, ledc_channel_config_t led_channel);
static int angle_to_duty(int angle);


void servo_init(){
    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 50,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_config);


    ledc_channel_config_t led_channel = {
        .gpio_num = SERVO_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&led_channel);

    servo_move(timer_config, led_channel);

}


// thsi function is to sweep with the servo motor from 0 to 180 degrees and back to 0 degrees. It uses a while loop to continuously sweep the servo motor. The angle variable is used to keep track of the current angle of the servo motor. The duty cycle is calculated based on the angle and set using the ledc_set_duty function. The ledc_update_duty function is called to update the duty cycle. A delay of 500ms is added between each angle change using vTaskDelay.
void servo_move(ledc_timer_config_t timer_config, ledc_channel_config_t led_channel){
   
    int angle;
    while (1) {

        for (angle = 0; angle <= 180; angle += 10) {
            int duty = angle_to_duty(angle); // Convert angle to duty cycle (0-1023)
            ledc_set_duty(led_channel.speed_mode, led_channel.channel, duty);
            ledc_update_duty(led_channel.speed_mode, led_channel.channel);
            vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500ms
        }
            
        for (angle = 180; angle >= 0; angle -= 10) {
            int duty = angle_to_duty(angle); // Convert angle to duty cycle (0-1023)
            ledc_set_duty(led_channel.speed_mode, led_channel.channel, duty);
            ledc_update_duty(led_channel.speed_mode, led_channel.channel);
            vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500ms
        }

    }
    
}
static void reset_servo(ledc_timer_config_t timer_config, ledc_channel_config_t led_channel){
    ledc_set_duty(led_channel.speed_mode, led_channel.channel, 0);
    ledc_update_duty(led_channel.speed_mode, led_channel.channel);
}

static int angle_to_duty(int angle) {
    int pulse_width = 500 + (angle * 2000 / 180); // Convert angle to pulse width (500-2500us)
    int duty = (pulse_width * 1023) / 20000; // Convert pulse width to duty cycle (0-1023)
    return duty;
}