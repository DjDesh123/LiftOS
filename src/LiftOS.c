#include "LiftOS.h"
#include "components/LED.h"
#include "esp_err.h"



QueueHandle_t queue;
QueueHandle_t Destination_Queue;


uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT,
};


void init_LiftOS(void){


    //ESP_ERROR_CHECK(uart_param_config(UART_NUM_0,&uart_config));

    uart_driver_install(UART_NUM_0,1024,1024,0,NULL,0);
    uart_vfs_dev_use_driver(UART_NUM_0);
    
    LED_Init();

    Button button = Button_Init();

    Servo_Init();

    Cab cab = Stepper_Init();

    run_LiftOS(&button, &cab);
}


void run_LiftOS(Button *button, Cab *cab){
    queue = xQueueCreate(5,sizeof(Floors));
    Destination_Queue = xQueueCreate(5,sizeof(Floors));


    // Check BOTH queues
    if (queue == NULL || Destination_Queue == NULL){
        printf("Failed to create queue\n");
        return;
    }


    if (xTaskCreate(Destination_Task,"Destination_Task",4096,cab,10,NULL) != pdPASS){
        printf("Failed to create Destination_Task\n");
        return;
    }


    bool buttonHandle = false;


    while (1){
        if (Button_Pressed_Check()){

            if(!buttonHandle){
                
                Floors txFloor = button->Floor_Position;

                if (xQueueSend(queue,&txFloor,0) != pdTRUE){
                    printf("Pickup queue full\n");
                    LED_On();
                }

                buttonHandle = true;
         
            }
        
        }else{
            buttonHandle = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


void Destination_Task(void *parameter)
{
    Cab *cab =(Cab *)parameter;

    Floors RequestedFloor;


    while (1)
    {
        switch (cab->states)
        {
            case CAB_IDLE:

                if (xQueueReceive(queue,&RequestedFloor,portMAX_DELAY) == pdTRUE){
                    cab->Desired_Floor = RequestedFloor;


                    Close_Door();


                    cab->states =CAB_MOVING_TO_PICKUP;
                }

                break;


            case CAB_MOVING_TO_PICKUP:

                Stepper_Movement(cab);


                cab->Floor_Position =cab->Desired_Floor;

                Open_Door();

                Get_User_Requested_Floor();


                cab->states = CAB_WAITING_FOR_DESTINATION;

                break;

            case CAB_WAITING_FOR_DESTINATION:

                if (xQueueReceive(Destination_Queue,&RequestedFloor,portMAX_DELAY) == pdTRUE){
                    cab->Desired_Floor = RequestedFloor;

                    Close_Door();


                    cab->states = CAB_MOVING_TO_DESTINATION;
                }

                break;


        
            case CAB_MOVING_TO_DESTINATION:

                Stepper_Movement(cab);

                cab->Floor_Position =cab->Desired_Floor;
                Open_Door();

                if (xQueueReceive(Destination_Queue,&RequestedFloor,0) == pdTRUE){
                    cab->Desired_Floor = RequestedFloor;


                    Close_Door();
                }
                else
                {
                  
                    cab->states = CAB_IDLE;
                }

                break;
        }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
}



static void Clear_Buffer(){
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        // discard remaining characters
    }
}


void Get_User_Requested_Floor(void)
{
    Floors RequestedFloor;

    int Value;
    char buffer[1024];

    char response;
    int validResponse;


    do{
        do{
            printf("What floor do you request? [0-3]: ");
            

            fgets(buffer,sizeof(buffer),stdin);

    
            validResponse = sscanf(buffer,"%d", &Value);
            
            if (validResponse != 1){
                printf("must be between 0 and 3! \n");
            }


            switch (Value){
                case 0:

                    RequestedFloor = GROUND_FLOOR;
                    break;


                case 1:

                    RequestedFloor = FIRST_FLOOR;
                    break;


                case 2:

                    RequestedFloor = SECOND_FLOOR;
                    break;


                case 3:

                    RequestedFloor = THIRD_FLOOR;
                    break;


                default:

                    printf("Invalid floor. Choose 0-3.\n");
                    break;
            }

        }while(validResponse !=1);


        printf("idk if this code is even doing its fucking job %s\n",buffer);

        if (xQueueSend(Destination_Queue,&RequestedFloor,0) != pdTRUE){
            printf("Destination queue full\n");
            LED_On();
        }

        Clear_Buffer();

        printf("Do you wish to enter any more floors? [y/n]: ");
        
        fgets(buffer,sizeof(buffer),stdin);

        sscanf(buffer,"%c",&response);


        response = tolower(response);


        if (response != 'y' && response != 'n'){
            printf("Please enter y or n\n");
        
        }


    }while (response != 'y' && response != 'n');


}