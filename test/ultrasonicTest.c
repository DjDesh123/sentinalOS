#include "unity.h"
#include "ultrasonicMaths.h"
#include <stdbool.h>


void test_ultrasonic_distance_check(void) {
    TEST_ASSERT_TRUE(distance_check(5.0f));  
    TEST_ASSERT_FALSE(distance_check(15.0f)); 
}
