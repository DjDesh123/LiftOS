#include "components/LED.h"



void LED_Init() {
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
}

void LED_On() {
    gpio_set_level(LED_PIN, 1);
}

void LED_Off() {
    gpio_set_level(LED_PIN, 0);
}