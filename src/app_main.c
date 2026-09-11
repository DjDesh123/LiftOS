#include <stdio.h>
#include "components/LED.h"
#include "components/button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "components/servo.h"
#include "components/stepper.h"




void app_main(void)
{
    LED_Init();
    Button_Init();
    Servo_Init();
    Stepper_Init();

    while (1) {
       
        if (Button_Pressed_Check()) {
            Stepper_Movement();
        }
    }
       
}