#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "Motor.hpp"
#include <driver/gpio.h>

#define MOTOR_HS_MODE           LEDC_HIGH_SPEED_MODE
#define MOTOR_HS_TIMER          LEDC_TIMER_0

Motor :: Motor(const int gpio_pin,const int frequency, const int channel,const int max_rpm, const int direction) 
{
  MOTOR_FREQUENCY = frequency;
  MOTOR_CHANNEL = channel;
  MOTOR_GPIO_PIN = gpio_pin;
  MOTOR_MAX_RPM = max_rpm;
  MOTOR_DIRECTION_PIN = direction;
  Motor_timer_config(MOTOR_FREQUENCY);
  Motor_channel_config(MOTOR_GPIO_PIN, MOTOR_CHANNEL);
}

void Motor :: Motor_timer_config(const int frequency) 
{
  ledc_timer_config_t motor_timer;
  motor_timer.bit_num = LEDC_TIMER_10_BIT;
  motor_timer.freq_hz = frequency;
  motor_timer.speed_mode = MOTOR_HS_MODE;
  motor_timer.timer_num = MOTOR_HS_TIMER;
  ledc_timer_config(&motor_timer);
}

void Motor :: Motor_channel_config(const int gpio_pin, const int channel) 
{
  ledc_channel_config_t motor_channel; 
  motor_channel.channel = static_cast<ledc_channel_t>(channel);
  motor_channel.duty = 0;
  motor_channel.gpio_num = gpio_pin;
  motor_channel.speed_mode = MOTOR_HS_MODE;
  motor_channel.timer_sel = MOTOR_HS_TIMER;
  ledc_channel_config(&motor_channel);
}

void Motor :: Motor_set_rpm(int percentage) 
{
  if(percentage < 0 )
  {
    percentage*= -1;
    Motor_set_direction(0); // backward
  }
  else
  {
    Motor_set_direction(1);
  }
  uint32_t duty = (float(percentage)/100)*1023; //1023 is max decimal number in 10 bit
  // float divide = float(target_rpm / MOTOR_MAX_RPM);
  // float result = divide*1023;
  // int duty = result;
  printf("duty : %i , max_rpm : %i, motor channel: %i  \n", duty, MOTOR_MAX_RPM, MOTOR_CHANNEL);
  ledc_set_duty(MOTOR_HS_MODE, static_cast<ledc_channel_t>(MOTOR_CHANNEL), duty);
  ledc_update_duty(MOTOR_HS_MODE, static_cast<ledc_channel_t>(MOTOR_CHANNEL));
}

void Motor :: Motor_set_direction(int direction)
{
  printf("%i\n", direction );
  gpio_set_direction(static_cast<gpio_num_t>(MOTOR_DIRECTION_PIN),GPIO_MODE_OUTPUT);
  gpio_set_level(static_cast<gpio_num_t>(MOTOR_DIRECTION_PIN),direction);
}