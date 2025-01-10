#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"

// GPIO Definitions
#define BUTTON_GPIO GPIO_NUM_0  // Button connected to GPIO 0
#define LED_GPIO    GPIO_NUM_2  // LED connected to GPIO 2

// Static variable to track LED state
static int led_state = 0;

// IRAM Attribute to place ISR in IRAM
IRAM_ATTR static void gpio_isr_handler(void *arg) {
    // Toggle LED state
    led_state = !led_state;  // Flip the state
    gpio_set_level(LED_GPIO, led_state);  // Set the new state
}

void app_main() {
    // Configure LED GPIO as output
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_config);

    // Initialize LED state (off)
    gpio_set_level(LED_GPIO, 0);

    // Configure Button GPIO as input with interrupt
    gpio_config_t button_config = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE // Interrupt on button press (falling edge)
    };
    gpio_config(&button_config);

    // Install GPIO ISR Service
    gpio_install_isr_service(0); // Use default interrupt service

    // Attach ISR handler to the button GPIO
    gpio_isr_handler_add(BUTTON_GPIO, gpio_isr_handler, NULL);

    printf("Press the button connected to GPIO %d to toggle the LED on GPIO %d.\n", BUTTON_GPIO, LED_GPIO);

    // Main loop does nothing; all logic is handled in the ISR
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
