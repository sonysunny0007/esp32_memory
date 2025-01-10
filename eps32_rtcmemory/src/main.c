#include <stdio.h>
#include <esp_sleep.h>
#include <esp_attr.h>

//Retain data in RTC memory
RTC_DATA_ATTR int retained_count=0;

void app_main() {
   printf("Retained count: %d\n", retained_count);
   retained_count++;

   printf("Entering to deep sleep for 10 seconds\n");
   esp_sleep_enable_timer_wakeup(10*1000000);
   esp_deep_sleep_start();
}
