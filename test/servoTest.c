#include "unity.h"
#include "components/servo/servoMaths.h"


void angle_to_duty_test() {
    // Test the angle_to_duty function with various angles
    TEST_ASSERT_EQUAL(500, angle_to_duty(0));
    TEST_ASSERT_EQUAL(1500, angle_to_duty(90));
    TEST_ASSERT_EQUAL(2500, angle_to_duty(180));
}



int runUnityTests() {
    UNITY_BEGIN();
    // Add your test cases here
    angle_to_duty_test();
    return UNITY_END();
}



void app_main() {
    runUnityTests();
}