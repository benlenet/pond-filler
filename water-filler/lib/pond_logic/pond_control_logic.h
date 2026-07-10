// pond_control_logic.h
typedef enum {
    VALVE_NO_CHANGE,
    VALVE_OPEN,
    VALVE_CLOSE
} ValveAction;

ValveAction evaluate_water_level(int current_water_reading);

