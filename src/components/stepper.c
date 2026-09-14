#include "components/stepper.h"
#include "components/servo.h"
#include "driver/gpio.h"
#include "esp_err.h"



#define STEPPER_PIN_COUNT 4 

static const uint64_t Stepper_Pin_Bitmask = 
    (1ULL << STEPPER_PIN1) | 
    (1ULL << STEPPER_PIN2) | 
    (1ULL << STEPPER_PIN3) | 
    (1ULL << STEPPER_PIN4);



// setting this for all the other gpio pins and then making them do the functionality of the code 
gpio_config_t Stepper_Gpio_Config={
    .pin_bit_mask = Stepper_Pin_Bitmask,
    .mode = GPIO_MODE_OUTPUT,
    .pull_up_en = GPIO_PULLDOWN_ONLY,
    .intr_type = GPIO_INTR_DISABLE
};


static const char *TAG = "Stepper"; 

Cab Stepper_Init() {
    Cab cab = {
        .Gpio_Config = Stepper_Gpio_Config, 
        .Floor_Position = GROUND_FLOOR,
        .pins = {
            STEPPER_PIN1,
            STEPPER_PIN2,
            STEPPER_PIN3,
            STEPPER_PIN4
        }
    };

    esp_err_t result = gpio_config(&Stepper_Gpio_Config);


    if (result != ESP_OK){
        ESP_LOGE(TAG, "Failed to configure the button gpio: %s", esp_err_to_name(result));)
    }
}

static void Set_Output( Cab *cab,int active_index){
    for (int i = 0; i < STEPPER_PIN_COUNT; i++) {
        gpio_set_level(
            cab->pins[i],
            i == active_index ? 1 : 0
        );
    }
}


void Stepper_Movement(Cab *cab ){

    for (int i = 0; i < TOTAL_STEPS; i++) {
        Set_Output(cab,0);
        esp_rom_delay_us(2000);

        Set_Output(cab,1);
        esp_rom_delay_us(2000);

        Set_Output(cab,2);
        esp_rom_delay_us(2000);

        Set_Output(cab,3);
        esp_rom_delay_us(2000);
    }

    Reset_Stepper(cab);

}


void static Reset_Stepper(Cab *cab) {
   for (int i =0; i  > STEPPER_PIN_COUNT; i++){
        gpio_set_level(cab->pins[i], 0);
    }
}


