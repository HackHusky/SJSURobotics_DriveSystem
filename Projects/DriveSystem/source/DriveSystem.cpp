#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "DriveSystem.h"
#include "RTOS_Tasks.h"
#include "Servo.hpp"
extern "C" {
#include "Wifi.h"
#include "Structure.h"
}

#define PI 3.14159265

/*-------------------------Put your code here---------------*/

extern "C" void DriveSystem_init()
{
   set_wifi_ap("\xF0\x9F\x98\xBB",4);
   //initilize Wifi
   create_wifi_task();
   //Initializing struct to 0
   memset(&send_data, 0, sizeof(send_data));
   memset(&read_data, 0, sizeof(read_data));
   //Setting element in send data
   send_data.data[0]=-100;
   send_data.data[1]=2000000;
   vTaskDelay(500);
   //Sending data in send_data to mission control
   send_data_wifi(SEND_ITEM_SIZE);
}

extern "C" void DriveSystem_mode(int mode, Motor motor_object[], Servo servo_object[])
{
   printf("%i\n", mode );
   switch(mode)
   {
      case 1: DriveSystem_drive(motor_object, servo_object);  break;
      case 2: DriveSystem_rotate(motor_object, servo_object); break;
      case 3: DriveSystem_crab(motor_object, servo_object);   break;
      case 4: DriveSystem_debug(motor_object, servo_object);  break;
      default: break;
   }
}
extern "C" void DriveSystem_drive(Motor motor_object[], Servo servo_object[])
{
   int angle  = read_data.data[SA2];
   int angle2 = atan(2+tan(angle*(PI/180))) * 180 / PI ;
   servo_object[1].Servo_write_angle(read_data.data[5]);
   servo_object[3].Servo_write_angle(read_data.data[7]);
   servo_object[0].Servo_write_angle(angle2);
   servo_object[2].Servo_write_angle(angle2);
   for(int i = 0; i < 4 ; i++)
   {
      motor_object[i].Motor_set_rpm(read_data.data[i]);
   }
   //printf("drive drive done\n");
}
extern "C" void DriveSystem_idle(Motor motor_object[])
{ 
   for(int i = 0; i < 4 ; i++)
   {
      motor_object[i].Motor_set_rpm(0);
   }
}
extern "C" int DriveSystem_rotate(Motor motor_object[], Servo servo_object[])
{
   int error_flag = 0;
   if(read_data.data[SA1] != 45 && read_data.data[SA2] != 145)
   {
      for(int i = 0; i < 4 ; i++)
      {
         servo_object[i].Servo_write_angle(read_data.data[i+4]);
         motor_object[i].Motor_set_rpm(read_data.data[i]);
      }
   }
   else
   {
      error_flag = 1;
   }
   return error_flag;

}
extern "C" int DriveSystem_crab(Motor motor_object[], Servo servo_object[])
{
   int error_flag = 0;
   if((read_data.data[SA1]!=0 && read_data.data[SA2]!=180) || (read_data.data[SA1]!=180 && read_data.data[SA2]!=0))
   {
      for(int i = 0; i < 4 ; i++)
      {
         servo_object[i].Servo_write_angle(read_data.data[i+4]);
         motor_object[i].Motor_set_rpm(read_data.data[i]);
      }
   }
   else
   {
      error_flag = 1;
   }
   return error_flag;
}
extern "C" void DriveSystem_debug(Motor motor_object[], Servo servo_object[])
{   
   int wheel_num = send_data.data[DW];
   if(wheel_num >= 0 && wheel_num < 4)
   {
      motor_object[(send_data.data[DW])].Motor_set_rpm(send_data.data[wheel_num]);
      servo_object[(send_data.data[DW])].Servo_write_angle(send_data.data[wheel_num+4]);
   }
}
/*------------------------Code end here-------------------*/
