// pond_control_logic.c
#include "pond_control_logic.h"
#include "sensor_macro.h"

ValveAction evaluate_water_level(int current_water_reading) {
    if (current_water_reading < WATER_MIN_VAL) {
        return VALVE_OPEN;
    } 
    if (current_water_reading > WATER_MIN_VAL) {
        return VALVE_CLOSE;
    }
    return VALVE_NO_CHANGE;
}