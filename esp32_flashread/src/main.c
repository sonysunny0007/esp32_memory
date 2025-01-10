#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_flash.h"
#include "esp_log.h"

#define FLASH_READ_ADDR 0x100000  // Example address in flash
#define BUFFER_SIZE 256           // Buffer size for reading

static const char *TAG = "FLASH_READ";

void app_main(void) {
    uint8_t buffer[BUFFER_SIZE] = {0};

    // Initialize the flash chip instance
    esp_flash_t *flash_chip = esp_flash_default_chip;

    // Read data from flash memory using the new API
    esp_err_t ret = esp_flash_read(flash_chip, buffer, FLASH_READ_ADDR, BUFFER_SIZE);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read flash memory: %s", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "Flash memory read successful. Data:");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
