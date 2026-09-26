#ifndef SERVO_H
#define SERVO_H


#include "driver/ledc.h"


#define MIN_PULSE_WIDTH 500  // Minimum pulse width in microseconds
#define MAX_PULSE_WIDTH 2500 // Maximum pulse width in microseconds
#define SERVO_PIN GPIO_NUM_25 


void Servo_Init();
void Open_Door();
void Close_Door();


#endif