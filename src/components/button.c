#include "components/button.h"


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


typedef struct{
    int Floor_Position;
    int Press_Check;
} Button



// defines the tag at the top of the file for logging purposes
static const char *TAG = "Button";


//sets up the button pin as an input and with a pull down resistor
void Button_Init() {
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLDOWN_ONLY);

}


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




