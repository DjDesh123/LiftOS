#include "components/button.h"
#include "components/stepper.h"
#include <stdint.h>
#include "driver/uart.h"
#include "esp_err.h"
#include "hal/uart_types.h"



#define UART_NUM UART_NUM_00

uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
    .rx_flow_ctrl_thresh = 122
};

ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));




void init_LiftOS() {
    LED_Init();
    Button button = Button_Init();
    Servo_Init();
    Cab cab = Stepper_Init();

}


void run_LiftOS() {
    while (1) {
        if (Button_Pressed_Check()) {
            
    }
    }
}

// we need to track the floro the cart is one and the floor that the button is located 



static bool Floors_Check(Button *button, Cab *cab){
    if (button->Floor_Position == cab->Floor_Position){
        //open the door
    }
    else{
        //move the cart to that floor 
    }
}







// you call the elevator by pushing the button 
// first it checks if youre at the same floor if so then we add the door opening 
// then we need to set up a a quee as its fifo
// then we need to add to stepper  is desired stop somewhow then we can change the cab struct state
