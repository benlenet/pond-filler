
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

/**
 * @brief Example task function
 * 
 * @param pvParameters Task parameters (can be NULL if not needed)
 */
static void task_example(void *pvParameters) {
    // Cast parameter if needed
    // int task_id = (int)pvParameters;
    
    while (1) {
        ESP_LOGI(TAG, "Task running - tick count: %ld", xTaskGetTickCount());
        
        // Add your task logic here
        
        // Delay for 1000ms (1 second)
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    // Task cleanup (if task is designed to exit)
    vTaskDelete(NULL);
}

/**
 * @brief Another example task with different priority
 * 
 * @param pvParameters Task parameters
 */
static void task_secondary(void *pvParameters) {
    while (1) {
        ESP_LOGI(TAG, "Secondary task running");
        
        // Add your task logic here
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
    vTaskDelete(NULL);
}

void app_main() {
    ESP_LOGI(TAG, "Starting FreeRTOS tasks...");
    
    // Create first task
    // xTaskCreate(
    //     task_example,           // Task function
    //     "task_example",         // Task name (for debugging)
    //     2048,                   // Stack size in bytes (512 * 4 = 2048 bytes)
    //     NULL,                   // Task parameters
    //     1,                      // Priority (0 = lowest, higher number = higher priority)
    //     NULL                    // Task handle (NULL if not needed)
    // );
    
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