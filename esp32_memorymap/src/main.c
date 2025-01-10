#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_attr.h"


//Allocate a variable in IRAM
IRAM_ATTR int iram_var=10;

//Allocate a variable in RTC fast memory
RTC_FAST_ATTR int rtc_fast_var =5;

//Allocate a variable in RTC slow memory
RTC_SLOW_ATTR int rtc_slow_var =11;






void app_main() {

    //General dram allocation
    int dram_var=50;

    //Allocate memory dynamically
    int *dynamic_var = (int *)malloc(sizeof(int));
    if(dynamic_var){
        *dynamic_var=50;
    }

    printf("IRAM variable address: %p\n", (void *)&iram_var);
    printf("RTC fast memory variable address: %p\n", (void *)&rtc_fast_var);
    printf("RTC slow memory variable address: %p\n", (void *)&rtc_slow_var);
    printf("DRAM variable address: %p\n", (void *)&dram_var);
    printf("Dynamic memory variable address: %p\n", (void *)&dynamic_var);

    //clean up
    free(dynamic_var);
}
