#include "components/servo.h"

void Stepper_Init() {
    // Initialize the stepper motor
    gpio_set_direction(STEPPER_PIN1, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEPPER_PIN2, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEPPER_PIN3, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEPPER_PIN4, GPIO_MODE_OUTPUT);

}

//delay for 2 seconds
void Stepper_Movement(){

    for (int i = 0; i < TOTAL_STEPS; i++) {
        gpio_set_level(STEPPER_PIN1, 1);
        gpio_set_level(STEPPER_PIN2, 0);
        gpio_set_level(STEPPER_PIN3, 0);
        gpio_set_level(STEPPER_PIN4, 0);
        esp_rom_delay_us(2000);

        gpio_set_level(STEPPER_PIN1, 0);
        gpio_set_level(STEPPER_PIN2, 1);
        gpio_set_level(STEPPER_PIN3, 0);
        gpio_set_level(STEPPER_PIN4, 0);
        esp_rom_delay_us(2000);

        gpio_set_level(STEPPER_PIN1, 0);
        gpio_set_level(STEPPER_PIN2, 0);
        gpio_set_level(STEPPER_PIN3, 1);
        gpio_set_level(STEPPER_PIN4, 0);
        esp_rom_delay_us(2000);

        gpio_set_level(STEPPER_PIN1, 0);
        gpio_set_level(STEPPER_PIN2, 0);
        gpio_set_level(STEPPER_PIN3, 0);
        gpio_set_level(STEPPER_PIN4, 1);
        esp_rom_delay_us(2000);
    }

    Reset_Stepper();

}


void static Reset_Stepper() {
    gpio_set_level(STEPPER_PIN1, 0);
    gpio_set_level(STEPPER_PIN2, 0);
    gpio_set_level(STEPPER_PIN3, 0);
    gpio_set_level(STEPPER_PIN4, 0);
}

