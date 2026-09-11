#ifndef STEPPER_H
#define STEPPER_H




#define STEPPER_PIN1 GPIO_NUM_32
#define STEPPER_PIN2 GPIO_NUM_14
#define STEPPER_PIN3 GPIO_NUM_27
#define STEPPER_PIN4 GPIO_NUM_26

void Stepper_Init();
void Stepper_Movement();
void static Reset_Stepper();




#endif // STEPPER_H