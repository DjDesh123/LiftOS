typedef enum{
    GROUND_FLOOR,
    FIRST_FLOOR,
    SECOND_FLOOR,
    THIRD_FLOOR
}Floors;


typedef struct{
    int Floor_Position;
    bool Press_Check;
} Button




void init_LiftOS() {
    LED_Init();
    Button_Init();
    Servo_Init();
    Stepper_Init();
}

void run_LiftOS() {
    while (1) {
        if (Button_Pressed_Check()) {
            
    }
    }
}




