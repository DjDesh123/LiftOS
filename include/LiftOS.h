#ifndef LIFTOS_H
#define LIFTOS_H


#include "components/button.h"
#include "components/stepper.h"
#include "components/servo.h"
#include "components/LED.h"




#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "portmacro.h"
#include "driver/uart.h"
#include "driver/uart_vfs.h"
#include "hal/uart_types.h"
#include "soc/clk_tree_defs.h"


void init_LiftOS(void);
void run_LiftOS(Button *button, Cab *cab);
void Destination_Task(void *parameter);
void Get_User_Requested_Floor(void);




#endif // LIFTOS_H