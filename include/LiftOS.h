#ifndef LIFTOS_H
#define LIFTOS_H


#include "components/button.h"
#include "components/stepper.h"
#include "components/servo.h"
#include "components/LED.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "portmacro.h"


void init_LiftOS(void);
void run_LiftOS(Button *button, Cab *cab);
void Destination_Task(void *parameter);
void Get_User_Requested_Floor(void);
static void Clear_Buffer(void);


QueueHandle_t queue;
QueueHandle_t Destination_Queue;


#endif // LIFTOS_H