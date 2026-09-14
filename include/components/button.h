#ifndef Button_H
#define Button_H

#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON_PIN GPIO_NUM_15

Button Button_Init();
int Button_Pressed_Check();

#endif