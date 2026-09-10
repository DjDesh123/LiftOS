#include "components/stepper.h"
#include "driver/gpio.h"

#define TOTAL_STEPS 512 

void Stepper_Init() {
    // Initialize the stepper motor
    gpio_set_direction(STEPPER_PIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEPPER_PIN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEPPER_PIN3, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEPPER_PIN4, GPIO_MODE_OUTPUT);

}


void Stepper_Movement(){
        gpio_set_level(STEPPER_PIN1, 1);
        gpio_set_level(STEPPER_PIN2, 0);
        gpio_set_level(STEPPER_PIN3, 0);
        gpio_set_level(STEPPER_PIN4, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        gpio_set_level(STEPPER_PIN1, 0);
        gpio_set_level(STEPPER_PIN2, 1);
        gpio_set_level(STEPPER_PIN3, 0);
        gpio_set_level(STEPPER_PIN4, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        gpio_set_level(STEPPER_PIN1, 0);
        gpio_set_level(STEPPER_PIN2, 0);
        gpio_set_level(STEPPER_PIN3, 1);
        gpio_set_level(STEPPER_PIN4, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        gpio_set_level(STEPPER_PIN1, 0);
        gpio_set_level(STEPPER_PIN2, 0);
        gpio_set_level(STEPPER_PIN3, 0);
        gpio_set_level(STEPPER_PIN4, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);
}


