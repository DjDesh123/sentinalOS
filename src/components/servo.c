#include "components/servo.h"


#define SERVO_PIN 23

ledc_timer_config_t ledc_timer = {
    .ledc_mode = LEDC_LOW_SPEED_MODE,
    .ledc_timer = LEDC_TIMER_0,
    .freq_hz = 50,
    .ledc_clk_cfg = LEDC_AUTO_CLK,
};
ledc_timer_config(&ledc_timer);


ledc_channel_config_t led_channel ={
    
};