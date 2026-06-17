
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "water_sensor.h"
#include "sensor_macro.h"

#define WATER_SENSOR_DELAY_MS 500
#define WATER_SENSOR_HOLD_MS  200

static const char *TAG = "MAIN";
static int water_reading;

/**
 * @brief Reads analog value from GPIO_WATER_DATA and prints
 * 
 * @param pvParameters Task parameters (can be NULL if not needed)
 */
static void water_sensor(void *pvParameters) {

    adc_oneshot_unit_handle_t adc_handle;
    adc_init(&adc_handle);
    // max value is 250, no water is 0, lowest value of resistor is 200. 
    while (1) {
        gpio_set_level(GPIO_LED, 1);
        gpio_set_level(GPIO_WATER_EN, 1);
        vTaskDelay(pdMS_TO_TICKS(WATER_SENSOR_HOLD_MS));  // Increased stabilization time
        
        // Average 10 samples with longer intervals
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += adc_read(&adc_handle);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        water_reading = sum / 10;
        
        ESP_LOGI(TAG, "Water Analog Level: %d", water_reading);
        gpio_set_level(GPIO_LED, 0);
        gpio_set_level(GPIO_WATER_EN, 0);
        
        // set to sleep for longer after reading
        vTaskDelay(pdMS_TO_TICKS(WATER_SENSOR_DELAY_MS));  // Longer interval between measurements
    }
    
    // Task cleanup (if task is designed to exit)
    vTaskDelete(NULL);
}

/**
 * @brief Another example task with different priority
 * 
 * @param pvParameters Task parameters
 */
static void nmos(void *pvParameters) {
    while (1) {
        ESP_LOGI(TAG, "Activate");
        
        // Add your task logic here
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
    vTaskDelete(NULL);
}

void app_main() {

    gpio_init();
    

    ESP_LOGI(TAG, "Starting FreeRTOS tasks...");
    
    // Create first task
    xTaskCreate(
        water_sensor,           // Task function
         "water_sensor",         // Task name (for debugging)
        2048,                   // Stack size in bytes (512 * 4 = 2048 bytes)
        NULL,                   // Task parameters
        1,                      // Priority (0 = lowest, higher number = higher priority)
        NULL                    // Task handle (NULL if not needed)
    );
    
    // Create second task
    // xTaskCreate(
    //     task_secondary,
    //     "task_secondary",
    //     2048,
    //     NULL,
    //     2,                      // Higher priority than task_example
    //     NULL
    // );
    
    ESP_LOGI(TAG, "All tasks created");
}