#ifndef STEPPER_H
#define STEPPER_H


#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_rom_sys.h"
#include "soc/gpio_num.h"

#define TOTAL_STEPS 512 
#define STEPPER_PIN1 GPIO_NUM_32
#define STEPPER_PIN2 GPIO_NUM_14
#define STEPPER_PIN3 GPIO_NUM_27
#define STEPPER_PIN4 GPIO_NUM_26

// holds the floors
typedef enum {
    GROUND_FLOOR,
    FIRST_FLOOR,
    SECOND_FLOOR,
    THIRD_FLOOR
} Floors;



// creates a struct for the cart to make it be able to hold a position
typedef struct{
    gpio_config_t Gpio_Config;
    Floors Floor_Position;
    gpio_num_t pins[4];
    Floors Desired_Floor;
  
} Cab;

Cab Stepper_Init();
void Stepper_Movement(Cab *cab);
static void Set_Output(Cab *cab, int active_index);





#endif // STEPPER_H