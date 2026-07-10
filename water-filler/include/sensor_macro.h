#ifndef SENSOR_MACRO_H
#define SENSOR_MACRO_H


// define for water level data
#define GPIO_WATER_DATA GPIO_NUM_4
#define GPIO_WATER_EN   GPIO_NUM_3
#define GPIO_LED        GPIO_NUM_8

// define for NMOS gate pin
#define GPIO_GATE       GPIO_NUM_5


#define WATER_SENSOR_DELAY_MS 500
#define WATER_SENSOR_HOLD_MS  200

#define WATER_MAX_VAL         250
#define WATER_MIN_VAL         200
#define WATER_SAMPLE_RATE     10

#define SOLENOID_DELAY_MS     2000   


#endif