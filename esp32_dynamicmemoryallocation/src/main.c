#include <stdio.h>
#include "esp_heap_caps.h"

void app_main() {
    // Allocate memory suitable for DMA
    uint8_t *dma_buffer = (uint8_t *)heap_caps_malloc(1024, MALLOC_CAP_DMA);
    if (!dma_buffer) {
        printf("Failed to allocate DMA buffer.\n");
        return;
    }

    printf("DMA buffer allocated at address: %p\n", (void *)dma_buffer);

    // Use the buffer (e.g., fill with data for SPI transfer)
    for (size_t i = 0; i < 1024; i++) {
        dma_buffer[i] = (uint8_t)(i % 256);
    }

    // Free buffer
    free(dma_buffer);
    printf("DMA buffer freed.\n");
}