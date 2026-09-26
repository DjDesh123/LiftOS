#ifndef STEPPER_H
#define STEPPER_H


#include "driver/gpio.h"
#include "components/floors.h"
#include "soc/gpio_num.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"



#define STEPPER_PIN_COUNT 4 

#define TOTAL_STEPS 512 
#define STEPPER_PIN1 GPIO_NUM_32
#define STEPPER_PIN2 GPIO_NUM_14
#define STEPPER_PIN3 GPIO_NUM_27
#define STEPPER_PIN4 GPIO_NUM_26


typedef enum{
    CAB_IDLE,
    CAB_MOVING_TO_PICKUP,
    CAB_WAITING_FOR_DESTINATION,
    CAB_MOVING_TO_DESTINATION    
} Cab_States;


// creates a struct for the cart to make it be able to hold a position
typedef struct{
    gpio_config_t Gpio_Config;
    Floors Floor_Position;
    gpio_num_t pins[4];
    Floors Desired_Floor;
    Cab_States states;
  
} Cab;

Cab Stepper_Init();
void Stepper_Movement(Cab *cab);
static void Set_Output(Cab *cab, int active_index);





#endif // STEPPER_H