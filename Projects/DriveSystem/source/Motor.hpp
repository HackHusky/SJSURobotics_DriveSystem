#ifndef MOTOR_H
#define MOTOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "Motor.hpp"
#include <driver/gpio.h>


class Motor
{
     private :
          int MOTOR_MAX_RPM;
          int MOTOR_FREQUENCY;         //Servo frequency
          int MOTOR_CHANNEL;             //Servo Timer channel
          int MOTOR_GPIO_PIN;                  //Servo Pin 
          int MOTOR_DIRECTION_PIN;
     public :
          Motor(const int gpio_pin, const int frequency, const int channel,const int max_rpm, const int direction);
          void Motor_timer_config(const int frequency);
          void Motor_channel_config(const int gpio_pin, const int channel);
          void Motor_set_rpm(int target_rpm);
          void Motor_set_direction(int direction);
};

#endif