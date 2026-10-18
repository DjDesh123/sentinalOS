#include "servoMaths.h"
#include "include/servoTest.h"


void angle_to_duty_test(void) {
    // Test the angle_to_duty function with various angles
    TEST_ASSERT_EQUAL(25, angle_to_duty(0));
    TEST_ASSERT_EQUAL(76, angle_to_duty(90));
    TEST_ASSERT_EQUAL(127, angle_to_duty(180));
}
