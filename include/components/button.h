#ifndef Button_H
#define Button_H

#include "driver/gpio.h"
#include "components/floors.h"
#include "esp_log.h"
#include "esp_err.h"


#define BUTTON_PIN GPIO_NUM_15

typedef enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED
} ButtonState;


typedef struct{
    gpio_config_t Gpio_Config;
    Floors Floor_Position;
} Button;

Button Button_Init();
int Button_Pressed_Check();

#endif