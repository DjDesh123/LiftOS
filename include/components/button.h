#ifndef Button_H
#define Button_H

#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON_PIN GPIO_NUM_15

typedef enum {
    GROUND_FLOOR,
    FIRST_FLOOR,
    SECOND_FLOOR,
    THIRD_FLOOR
} Floors;


typedef struct{
    gpio_config_t Gpio_Config;
    Floors Floor_Position;
} Button;

Button Button_Init();
int Button_Pressed_Check();

#endif