#include <stdio.h>
#include <esp_system.h>
#include "esp_heap_caps.h"

void app_main() {
//Allocate 1MB in PSRAM
uint8_t *psram_buffer = (uint8_t *)heap_caps_malloc(1024*1024, MALLOC_CAP_SPIRAM);
if(!psram_buffer){
    printf("Failed to allocate PSRAM\n");
    return;
}

printf("PSRAM buffer allocated in address: %p\n", (void *)psram_buffer);

//use buffer
for(size_t i=0;i<1024;i++){
    psram_buffer[i]=(uint8_t)(i%256);
}

free(psram_buffer);
printf("PSRAM buffer freed\n");


}
