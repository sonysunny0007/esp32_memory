#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_heap_caps.h"

// ADC Configuration
#define ADC_CHANNEL ADC1_CHANNEL_0  // GPIO36 (VP)
#define ADC_WIDTH ADC_WIDTH_BIT_12  // 12-bit resolution
#define ADC_ATTEN ADC_ATTEN_DB_11   // Full range attenuation

// Buffer size for storing ADC readings
#define BUFFER_SIZE 100

void init_adc() {
    // Configure ADC width and attenuation
    adc1_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);
}

void read_sensor_task(void *param) {
    // Allocate memory in DRAM for ADC readings
    uint32_t *adc_buffer = (uint32_t *)heap_caps_malloc(BUFFER_SIZE * sizeof(uint32_t), MALLOC_CAP_8BIT);
    if (adc_buffer == NULL) {
        printf("Failed to allocate memory for ADC buffer\n");
        vTaskDelete(NULL);
        return;
    }

    printf("Successfully allocated memory for ADC buffer in DRAM.\n");

    int buffer_index = 0;
    while (1) {
        // Read ADC value
        uint32_t adc_reading = adc1_get_raw(ADC_CHANNEL);

        // Store reading in the allocated buffer
        adc_buffer[buffer_index++] = adc_reading;

        // Reset index and process data if buffer is full
        if (buffer_index >= BUFFER_SIZE) {
            printf("Buffer full. Processing data...\n");

            // Example processing: Compute average
            uint32_t sum = 0;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                sum += adc_buffer[i];
            }
            float average = sum / (float)BUFFER_SIZE;
            printf("Average ADC value: %.2f\n", average);

            // Reset buffer index
            buffer_index = 0;
        }

        // Print current ADC value
        printf("ADC Reading: %ld\n", adc_reading);

        // Delay for 100ms
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    // Free allocated memory (if the task is ever deleted)
    free(adc_buffer);
}

void app_main() {
    // Initialize ADC
    init_adc();

    // Create a task to read sensor data
    xTaskCreate(read_sensor_task, "Read Sensor Task", 4096, NULL, 5, NULL);
}
