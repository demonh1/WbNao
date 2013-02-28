#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <webots/robot.h>
#include <webots/supervisor.h>
#include <webots/servo.h>
#include <webots/receiver.h>
#include <webots/emitter.h>

#define TIME_STEP 32
#define SIZE_OF_POP 30

WbDeviceTag joint[24];

typedef struct param
{
  double Ahr;
  double Aar;
  double Ahp;
  double k;
  double T;
  double Ahpp;
  double Akp;
  
} param;

void get_servos();

void get_servos()
{
  joint[0] = wb_robot_get_device("HeadYaw");
  joint[1] = wb_robot_get_device("HeadPitch");
  joint[2] = wb_robot_get_device("RShoulderPitch");
  joint[3] = wb_robot_get_device("RShoulderRoll");
  joint[4] = wb_robot_get_device("RElbowYaw");
  joint[5] = wb_robot_get_device("RElbowRoll");
  joint[6] = wb_robot_get_device("RWristYaw");
  joint[7] = wb_robot_get_device("LShoulderPitch");
  joint[8] = wb_robot_get_device("LShoulderRoll");
  joint[9] = wb_robot_get_device("LElbowYaw");
  joint[10] = wb_robot_get_device("LElbowRoll");
  joint[11] = wb_robot_get_device("LWristYaw");
  joint[12] = wb_robot_get_device("RHipYawPitch");
  joint[13] = wb_robot_get_device("RHipRoll");
  joint[14] = wb_robot_get_device("RHipPitch");
  joint[15] = wb_robot_get_device("RKneePitch");
  joint[16] = wb_robot_get_device("RAnklePitch");
  joint[17] = wb_robot_get_device("RAnkleRoll");
  joint[18] = wb_robot_get_device("LHipYawPitch");
  joint[19] = wb_robot_get_device("LHipRoll");
  joint[20] = wb_robot_get_device("LHipPitch");
  joint[21] = wb_robot_get_device("LKneePitch");
  joint[22] = wb_robot_get_device("LAnklePitch");
  joint[23] = wb_robot_get_device("LAnkleRoll");
}

void init();

void init()
{
  int i;
  
  for (i=0;i<24;i++)
  {
    wb_servo_set_position(joint[i], 0);
  }
}

int main(int argc, char **argv)
{
  int i=0;
  int j=0;
  int temp=0;

  param param[SIZE_OF_POP];
  
  double time=0;
  
  char* mail;

  wb_robot_init();
  
  WbDeviceTag emitter = wb_robot_get_device("emitter");
    
  WbDeviceTag receiver = wb_robot_get_device("receiver");
  wb_receiver_enable(receiver, TIME_STEP);
  wb_robot_step(TIME_STEP);
  
  char first = 1;
  
  while (1)
  {
    if (wb_receiver_get_queue_length(receiver) < 0)
      break;
    for (j=0; j<SIZE_OF_POP; j++)
    {

      while (1)
      {
        wb_robot_step(TIME_STEP);
        if (wb_receiver_get_queue_length(receiver) > 0)
          {
            const double *message = wb_receiver_get_data(receiver);
            //printf("\n%g", message[0]);
            wb_receiver_next_packet(receiver);
            
            param[j].Ahr = message[0];
            param[j].Aar = message[1];
            param[j].Ahp = message[2];
            param[j].k = message[3];
            param[j].T = message[4];
            param[j].Ahpp = message[5];
            param[j].Akp = message[6];
            
            //param[j].Ahr = 0.104682;
            //param[j].Aar = 0.292435;
            //param[j].Ahp = 0.145007;
            //param[j].k = 0.637518;
            //param[j].T = 5.12747;
            
            break;
          }
      }

      
      get_servos();
      init();
      time = 0;
      //printf("\nsatan");
      do 
      {
      //HipRoll
      wb_servo_set_position(joint[13], param[j].Ahr*sin((6.28/param[j].T)*time));
      wb_servo_set_position(joint[17], -param[j].Aar*sin((6.28/param[j].T)*time));
      wb_servo_set_position(joint[19], param[j].Ahr*sin((6.28/param[j].T)*time));
      wb_servo_set_position(joint[23], -param[j].Aar*sin((6.28/param[j].T)*time));
      
      //HipPitch
      double HipPitchR0 = wb_servo_get_position(joint[14]);
      wb_servo_set_position(joint[14], param[j].Ahp*sin(-param[j].T/4+(6.28/param[j].T)*time)+HipPitchR0);
      double HipPitchL0 = wb_servo_get_position(joint[20]);
      wb_servo_set_position(joint[20], param[j].Ahp*sin(+param[j].T/4+(6.28/param[j].T)*time)+HipPitchL0);
      
      //KneePitch
      double KneePitchR0 = wb_servo_get_position(joint[15]);
      wb_servo_set_position(joint[15], -param[j].k*param[j].Ahp*sin(-param[j].T/4+(6.28/param[j].T)*time)+KneePitchR0);
      double KneePitchL0 = wb_servo_get_position(joint[21]);
      wb_servo_set_position(joint[21], -param[j].k*param[j].Ahp*sin(+param[j].T/4+(6.28/param[j].T)*time)+KneePitchL0);
      
      //AnklePitch
      double AnklePitchR0 = wb_servo_get_position(joint[16]);
      wb_servo_set_position(joint[16], 0.5*param[j].Ahp*sin(-param[j].T/4+(6.28/param[j].T)*time)+AnklePitchR0);
      double AnklePitchL0 = wb_servo_get_position(joint[22]);
      wb_servo_set_position(joint[22], 0.5*param[j].Ahp*sin(+param[j].T/4+(6.28/param[j].T)*time)+AnklePitchL0);
        
        time += TIME_STEP / 1000.0;
        //printf("\n%g", time);
      } while (wb_robot_step(TIME_STEP) != -1 && time < 60);
      wb_robot_step(TIME_STEP);
      mail = "fin";
      //printf("\n%s", mail);
      wb_emitter_send(emitter, mail, strlen(mail)+1);
      
      while (1)
      {
        wb_robot_step(TIME_STEP);
        const char *messagechar = wb_receiver_get_data(receiver);
        if (wb_receiver_get_queue_length(receiver)>0)
        {
          //printf("\n%s", messagechar);
          if (strcmp(messagechar, "next") == 0)
          {
            wb_receiver_next_packet(receiver);
            break;
          }
        } // если что-то получили
      } // ожидание завершения эксперимента
      //continue;
    }
  }


  wb_robot_cleanup();
  
  return 0;
}
