#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "hardware_interface.h"
#include "sensor_macro.h"
#include "pond_control_logic.h"

#define DEBUG_PRINT 1

static const char *TAG = "MAIN";

static int shared_water_reading = 0;
static SemaphoreHandle_t mutex; 

// Thread-safe setter
void set_water_reading(int val) {
    if (xSemaphoreTake(mutex, portMAX_DELAY)) {
        shared_water_reading = val;
        xSemaphoreGive(mutex);
    }
}

// Thread-safe getter
int get_water_reading(void) {
    int val = 0;
    if (xSemaphoreTake(mutex, portMAX_DELAY)) {
        val = shared_water_reading;
        xSemaphoreGive(mutex);
    }
    return val;
}

// retrieve adc reading from water sensor
static void water_sensor_task(void *pvParameters) {
    hw_init_sensors();
    
    while (1) {
        hw_set_indicator_led(1);
        hw_set_sensor_power(1);
        vTaskDelay(pdMS_TO_TICKS(WATER_SENSOR_HOLD_MS));
        
        int sum = 0;
        for (int i = 0; i < WATER_SAMPLE_RATE; i++) {
            sum += hw_read_water_level();
            vTaskDelay(pdMS_TO_TICKS(WATER_SENSOR_HOLD_MS));
        }
        
        set_water_reading(sum / WATER_SAMPLE_RATE);
        
        #if DEBUG_PRINT == 1
            printf("water level: %d\n", sum);
        #endif

        hw_set_indicator_led(0);
        hw_set_sensor_power(0);
        vTaskDelay(pdMS_TO_TICKS(WATER_SENSOR_DELAY_MS));
    }
}

// activate solenoid
static void solenoid_control_task(void *pvParameters) {
    while (1) {
        int current_level = get_water_reading();
        ValveAction action = evaluate_water_level(current_level);
        
        if (action == VALVE_OPEN) {
            hw_set_solenoid_valve(1);
        } else if (action == VALVE_CLOSE) {
            hw_set_solenoid_valve(0);
        }
        
        #if DEBUG_PRINT == 1
            printf("solenoid action: %d\n", action);
        #endif

        vTaskDelay(pdMS_TO_TICKS(SOLENOID_DELAY_MS));
    }
}

void app_main() {

    hw_init_sensors();
    mutex = xSemaphoreCreateMutex();
    assert(mutex);
    
    ESP_LOGI(TAG, "Reset Switch");
    

    xTaskCreate(
        water_sensor_task,           // Task function
         "water_sensor",         // Task name (for debugging)
        2048,                   // Stack size in bytes (512 * 4 = 2048 bytes)
        NULL,                   // Task parameters
        1,                      // Priority (0 = lowest, higher number = higher priority)
        NULL                    // Task handle (NULL if not needed)
    );
    
    // xTaskCreate(
    //     solenoid_control_task,
    //     "solenoid",
    //     2048,
    //     NULL,
    //     1,                      
    //     NULL
    // );
    
    ESP_LOGI(TAG, "All tasks created");
}