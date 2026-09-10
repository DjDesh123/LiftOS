#include <stdio.h>
#include "components/LED.h"
#include "components/button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



void app_main(void)
{
    LED_Init();
    Button_Init();

    while (1) {
        int button_state = Button_Pressed_Check();
        
        if (button_state == 1) {
            LED_On();
        } else {
            LED_Off();
        }
    }
       
}