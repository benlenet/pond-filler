#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include <driver/gpio.h>
#include <driver/uart.h>
#include <stdio.h>
#include "sensor_macro.h"
#include <esp_adc/adc_oneshot.h>

#define ADC_BITWIDTH       ADC_BITWIDTH_12
#define ADC_ATTEN          ADC_ATTEN_DB_12    
#define ADC_PIN            ADC_CHANNEL_1
#define ADC_UNIT           ADC_UNIT_1


#define UART_PORT_NUM      UART_NUM_0   // usually UART0 is connected to USB
#define UART_BAUD_RATE     115200
#define BUF_SIZE           1024
#define RD_BUF_SIZE        1024


void uart_init(void);
void gpio_init(void); 
int  adc_read(adc_oneshot_unit_handle_t* adc_handle);
void adc_init(adc_oneshot_unit_handle_t* adc_handle);
#endif