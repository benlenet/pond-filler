#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include <driver/gpio.h>
#include <driver/uart.h>
#include <stdio.h>
#include "sensor_macro.h"
#include <esp_adc/adc_oneshot.h>

#define ADC_BITWIDTH       ADC_BITWIDTH_12
#define ADC_ATTEN          ADC_ATTEN_DB_12    
#define ADC_PIN            ADC_CHANNEL_4
#define ADC_UNIT           ADC_UNIT_1


#define UART_PORT_NUM      UART_NUM_0   // usually UART0 is connected to USB
#define UART_BAUD_RATE     115200
#define BUF_SIZE           1024
#define RD_BUF_SIZE        1024

// set gpio, adc, and uart inits
void hw_init_sensors(void);
// turn onboard debugging light on
void hw_set_indicator_led(int state);
// turn water sensor on
void hw_set_sensor_power(int state);
// return oneshot adc sample
int  hw_read_water_level(void);
// set gate of NMOS
void hw_set_solenoid_valve(int state);

#endif