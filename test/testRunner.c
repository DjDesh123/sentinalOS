#include "unity.h"
#include "include/servoTest.h"
#include "include/ultrasonicTest.h"



void app_main(void) {
    UNITY_BEGIN();
    RUN_TEST(angle_to_duty_test);
    RUN_TEST(test_ultrasonic_distance_check);
    UNITY_END();
}