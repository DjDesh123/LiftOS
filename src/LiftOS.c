#include "LiftOS.h"


QueueHandle_t queue;
QueueHandle_t Destination_Queue;

void init_LiftOS(void)
{
    LED_Init();

    Button button = Button_Init();

    Servo_Init();

    Cab cab = Stepper_Init();

    run_LiftOS(&button, &cab);
}


void run_LiftOS(Button *button, Cab *cab)
{
    queue = xQueueCreate(5,sizeof(Floors));

    Destination_Queue = xQueueCreate(5,sizeof(Floors));


    // Check BOTH queues
    if (queue == NULL ||Destination_Queue == NULL){
        printf("Failed to create queue\n");
        return;
    }


    if (xTaskCreate(Destination_Task,"Destination_Task",4096,cab,10,NULL) != pdPASS){
        printf("Failed to create Destination_Task\n");
        return;
    }


    while (1)
    {
        if (Button_Pressed_Check()){
            Floors txFloor = button->Floor_Position;


            if (xQueueSend(queue,&txFloor,0) != pdTRUE){
                printf("Pickup queue full\n");
                LED_On();
            }
        }

        vTaskDelay(
            pdMS_TO_TICKS(10)
        );
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


static void Clear_Buffer(void)
{
    int c;

    while ((c = getchar()) != '\n' &&c != EOF){
    }
}


void Get_User_Requested_Floor(void)
{
    Floors RequestedFloor;

    int Value;

    char response = 'y';


    do{
        printf("What floor do you request? [0-3]: ");


     
        if (scanf("%d", &Value) != 1){
            printf("Invalid input\n");

            Clear_Buffer();

            continue;
        }


        switch (Value)
        {
            case 0:

                RequestedFloor = GROUND_FLOOR;
                 break;


            case 1:

                RequestedFloor = FIRST_FLOOR;
                break;


            case 2:

                RequestedFloor =SECOND_FLOOR;
                break;


            case 3:

                RequestedFloor = THIRD_FLOOR;
                break;


            default:

                printf("Invalid floor. Choose 0-3.\n");
                Clear_Buffer();
                continue;
        }


        if (xQueueSend(Destination_Queue,&RequestedFloor,0) != pdTRUE){
            printf("Destination queue full\n");
        }


        do
        {
            printf("Do you wish to enter any more floors? [y/n]: ");

            if (scanf(" %c",&response) != 1){
                Clear_Buffer();

                response = '\0';

                continue;
            }


            response =(char)tolower((unsigned char)response);
            Clear_Buffer();


            if (response != 'y' &&response != 'n')
            {
                printf("Please enter y or n\n");
            }


        } while (response != 'y' && response != 'n');
    } while (response == 'y');
}