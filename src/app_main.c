#include <stdio.h>
#include "components/LED.h"
#include "components/button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/servo.h"



void app_main(void)
{
    LED_Init();
    Button_Init();
    Servo_Init();

    while (1) {
        Open_Door();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1
        Close_Door();
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1
        
    }
       
}