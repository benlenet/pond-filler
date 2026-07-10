#include <unity.h>
#include "pond_control_logic.h"
#include "sensor_macro.h"


// This runs before every single test
void setUp(void) {
    // Initialization code if needed
}

// This runs after every single test
void tearDown(void) {
    // Clean up code if needed
}

void test_water_below_minimum_opens_valve(void) {
    int test_val = WATER_MIN_VAL - 10;
    ValveAction result = evaluate_water_level(test_val);
    TEST_ASSERT_EQUAL(VALVE_OPEN, result);
}

void test_water_above_maximum_closes_valve(void) {
    int test_val = WATER_MAX_VAL + 10;
    ValveAction result = evaluate_water_level(test_val);
    TEST_ASSERT_EQUAL(VALVE_CLOSE, result);
}

void test_water_in_range_does_nothing(void) {
    int test_val = (WATER_MIN_VAL + WATER_MAX_VAL) / 2;
    ValveAction result = evaluate_water_level(test_val);
    TEST_ASSERT_EQUAL(VALVE_NO_CHANGE, result);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_water_below_minimum_opens_valve);
    RUN_TEST(test_water_above_maximum_closes_valve);
    RUN_TEST(test_water_in_range_does_nothing);
    
    return UNITY_END();
}