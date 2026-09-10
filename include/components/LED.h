#ifndef LED_H
#define LED_H

#include <driver/gpio.h>
#define LED_PIN GPIO_NUM_19


void LED_Init();
void LED_On();
void LED_Off();





#endif