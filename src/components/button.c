#include "components/button.h"
#include "esp_err.h"


typedef enum {
    BUTTON_RELEASED,
    BUTTON_PRESSED
} ButtonState;

typedef enum{
    GROUND_FLOOR,
    FIRST_FLOOR,
    SECOND_FLOOR,
    THIRD_FLOOR
}Floors;


gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << BUTTON_PIN),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLDOWN_ONLY,
    .intr_type = GPIO_INTR_DISABLE
};


typedef struct{
    gpio_config_t Gpio_Config;
    Floors Floor_Position;
} Button;



// defines the tag at the top of the file for logging purposes
static const char *TAG = "Button";


//sets up the button pin as an input and with a pull down resistor
Button Button_Init() {

    Button button = {
        .Gpio_Config = io_conf,
        .Floor_Position = GROUND_FLOOR
        
    }
    
    esp_err_t result = gpio_config(&button.Gpio_Config);

    if (result !- ESP_OK){
        ESP_LOGE(TAG, "Failed to configure the button gpio: %s", esp_err_to_name(result));

    }
}

    return button;


int Button_Pressed_Check() {
    int button_state = gpio_get_level(BUTTON_PIN);

    if (button_state == 1) {
        return BUTTON_PRESSED;
    } else if (button_state == 0) {
        return BUTTON_RELEASED;
    } else {
        ESP_LOGI(TAG, "Invalid button state");
        return BUTTON_RELEASED;
    }
    
}




