#include "components/servo.h"


void Servo_Init() {
    // Initialize servo here

    ledc_timer_config_t timer_config = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = 50,  // 50Hz for servo
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_config);

    // configuring the pwm channel for the servo
    ledc_channel_config_t channel_config = {
        .gpio_num = SERVO_PIN,  // Change to your servo pin
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .duty = 0,  // Start with 0% duty cycle
        .hpoint = 0,
        .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&channel_config);


}

void Open_Door() {
    // Pulse width in microseconds for 90 degrees
    int pulse_width = MIN_PULSE_WIDTH + (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) * 0.75; 
    int duty = (int)(8191 * 0.075);  // 13-bit resolution, 0-8191
    // sets the servo to 90 degrees
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

}


void Close_Door() {
    // Pulse width in microseconds for 0 degrees
    int pulse_width = MIN_PULSE_WIDTH; 
    int duty = (int)(8191 * 0.025);  // 13-bit resolution, 0-8191
    // sets the servo to 0 degrees
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

}