# LiftOS

## Overview
LiftOS is an embedded elevator-contorl protoype developed in C for the ESP32 using the ESP-IDF framework and FreeRTOS. The project explores how an elevator system can be handled by using a state machine , with tasks and queues handling the floor requests and coordinating movement, door controls and user input.

The system uses a stepper motor to represent the elevator moving between floors and a servo motor to stimulate the doors of the elevator.

## Hardware and software
Hardware
- ESP32 development board
- Stepper motor connected through GPIO pins
- Servo motor for door simulation
- push button for requesting pick up
- Led for quee-related error indication

software 
- C
- ESP-IDF
- FreeRTOS
- PlatformIO
- CMake

The current GPIO assigments are defined in the componets header files:

- Button: GPIO 15
- Servo: GPIO 25
- LED: GPIO 19
- Stepper outputs: GPIOS 32, 14, 27 and 26

## Architecture
The project separates the main elevator logic from individual hardware components. app_main.c starts the application through init_LiftOS(). The initialisation function configures the UART, LED, button, servo and stepper. The main application creates two FreeRTOS queues: one for pickup requests and another for destination requests. A Destination_Task processes these requests and manages the elevator's state.The hardware drivers are kept in separate component files, making the GPIO, stepper and servo operations easier to maintain independently of the main control logic.

## Core concepts
- Finite-state machine: Represents the cab as idle, moving to pickup, waiting for a destination, or moving to a destination.
- FreeRTOS tasks: The destination task manages the elevator's movement and request-handling process.
- Queues: Separate queues store pickup and destination floor requests.
- GPIO: Handles the button, LED and stepper motor output pins.
- PWM: The ESP32's LEDC peripheral generates the servo control signal.
- UART: Provides console output and accepts destination-floor input.

## Current Features

- Initialisation of the ESP32 peripherals used by the project.
- Push-button input with a simple repeated-press prevention mechanism.
- A four-state elevator-control state machine.
- FreeRTOS queues for pickup and destination requests.
- Console-based destination entry for floors 0–3.
- Stepper motor output sequencing.
- Servo-based door opening and closing.
- Console status messages and LED indication when a request queue is full.

## Build and run

The project uses PlatformIO with the esp32doit-devkit-v1 board environment and the ESP-IDF framework.

1. Clone or download this repository.
2. Open the project in Visual Studio Code with PlatformIO installed.
3. Connect the ESP32 development board.
4. Select the esp32doit-devkit-v1 environment.
5. Build the project and upload the firmware.
6.Open the serial monitor at 115200 baud to view status messages and enter destination requests.

The motor wiring and GPIO assignments must match the configuration in the source code. Successful compilation and physical operation should be verified on the target hardware.

## Limitations

- Stepper movement currently uses a fixed number of steps rather than calculating movement from the current and requested floors.
- The pickup button's floor position is initialised to the ground floor and is not updated by the current input logic.
- Destination input validation needs improvement to handle invalid numbers and out-of-range values safely.
- The servo control functions contain unused pulse-width calculations, and its movement should be checked against the physical servo.
- The test directory currently contains PlatformIO testing guidance rather than implemented automated tests.
- Hardware behaviour, timing and request handling still require further testing. This is an educational prototype, not a safety-certified elevator controller.

## Future improvements

- Calculate the stepper movements from the current floor to the requested destination
- improve the validation and handle the invalid request properly
- add automated tests for floor selection, state transition and request hadnling
- improve error handling and loggin
- test the hardware behavior and refine motor timing
- improve quese hadnling and docuemtn the hardware wiring.
