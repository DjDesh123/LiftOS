



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

// we need to track the floro the cart is one and the floor that the button is located 



void static Floors_Check(){
    if (button.Floor_Position() == cab.Floor_Position()){
        //open the door
    }
    else{
        //move the cart to that floor 
    }
}







