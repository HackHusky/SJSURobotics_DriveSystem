#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "DriveSystem.h"
#include "RTOS_Tasks.h"
#include "Servo.hpp"
#include "Motor.hpp"

using namespace std;

extern "C" void app_main()
{
    uint32_t duty;
    printf("DriveSystem Testing \n");
    DriveSystem_init();
    xTaskCreate(vDriveTask, "vDriveTask", 4096, NULL, 1, NULL);

    // xTaskCreate(vReadDataTask, "vReadDataTask", 4096, NULL, 1, NULL);
    // // Servo(const int gpio_pin, const int frequency, const int channel,
    // //       const uint32_t max_pulse, const uint32_t min_pulse,const uint32_t max_degree);
    // Servo servo1(18,50,0,2500,500,270);
    // while(1){
    //   for(int i=0;i<27;i++)
    //   {
    //     servo1.Sero_write_angle(i*10);
    //   //duty = servo1.Servo_per_degree_init(20);
    //   //printf("%i\n", duty );
    //   };
    // };
    // int gpio_pin1  = 18;
    // int frequency1 = 25000;
    // int channel1   = 0;
    // int max_rpm1   = 300;

    // int gpio_pin2  = 19;
    // int frequency2 = 25000;
    // int channel2   = 1;
    // int max_rpm2   = 300;
    // Motor motor1(gpio_pin1, frequency1, channel1, max_rpm1); 
    // Motor motor2(gpio_pin2, frequency2, channel2, max_rpm2); 
    // motor1.Motor_set_rpm(150);

    // while(1){
    //         //printf("Testing\n");
    // };

}
