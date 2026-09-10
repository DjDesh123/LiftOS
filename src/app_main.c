#include <stdio.h>
#include "components/LED.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



void app_main(void)
{
    LED_Init();

    while (1) {
        LED_On();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        LED_Off();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}