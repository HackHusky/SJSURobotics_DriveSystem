#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "DriveSystem.h"
#include "Servo.hpp"
#include "Motor.hpp"
extern "C" {
#include "Wifi.h"
#include "Structure.h"
}

const int motor_gpio[4] = {32,33,2,27};
const int motor_frequency = 30000;
const int motor_channel[4] = {0,1,2,3};
const int motor_max_rpm = 600;
const int motor_direction_pin[4] = {23,1,5,6};
const int motor_brake_pin[4] = {22,3,18,17};
const int motor_hall_pin[4] = {36,38,34,35};

const int servo_gpio[4] = {25,4,0,26};
const int servo_frequency = 50;
const int servo_channel[4] = {0,1,2,3};
const uint32_t servo_max_pulse = 2500;
const uint32_t servo_min_pulse = 500;
const uint32_t servo_max_degree = 330; 


extern "C" void vReadDataTask(void *pvParameters){
  while(1){
     vTaskDelay(500);
     //read data from mission control.
     read_data_wifi(READ_ITEM_SIZE);
     printf("read data 1 : %i\n", read_data.data[1]);
  }
}

extern "C" void vDriveTask(void *pvParameters)
{
  int current_timestamp;
  int previous_timestamp=0;
  bool initial_flag = true;
  Motor motor[4] = 
  {
    {motor_gpio[0],motor_frequency,motor_channel[0],motor_max_rpm,motor_direction_pin[0]},
    {motor_gpio[1],motor_frequency,motor_channel[1],motor_max_rpm,motor_direction_pin[1]},
    {motor_gpio[2],motor_frequency,motor_channel[2],motor_max_rpm,motor_direction_pin[2]},
    {motor_gpio[3],motor_frequency,motor_channel[3],motor_max_rpm,motor_direction_pin[3]}
  };
  Servo servo[4] =
  {
    {servo_gpio[0],servo_frequency,servo_channel[0],servo_max_pulse,servo_min_pulse,servo_max_degree},
    {servo_gpio[1],servo_frequency,servo_channel[1],servo_max_pulse,servo_min_pulse,servo_max_degree},
    {servo_gpio[2],servo_frequency,servo_channel[2],servo_max_pulse,servo_min_pulse,servo_max_degree},
    {servo_gpio[3],servo_frequency,servo_channel[3],servo_max_pulse,servo_min_pulse,servo_max_degree}
  };
  while(1)
  {
    //read data from mission control.
    current_timestamp = read_data_wifi(READ_ITEM_SIZE);
    //printf("current_timestamp: %i \n", current_timestamp);
    //servo1.Sero_write_angle(read_data.data[1]);
    if(initial_flag == false)
    {
      //check for heartbeat, if no heartbeat go to idle.
      if(current_timestamp != previous_timestamp )
      {
        printf("Drive Execution \n");  
        DriveSystem_mode(read_data.data[M],motor,servo);
          vTaskDelay(50);
      }
      else
      {
        //printf("Drive Idle\n");
        DriveSystem_idle(motor);
      }
    }
    else  
    {
      DriveSystem_mode(read_data.data[M],motor,servo);
    }
    initial_flag = false;
    previous_timestamp = current_timestamp;
    vTaskDelay(1);
    printf("Servo task end\n");
  }
}
