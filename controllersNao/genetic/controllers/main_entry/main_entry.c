#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <webots/robot.h>
#include <webots/supervisor.h>
#include <webots/servo.h>
#include <webots/emitter.h>
#include <webots/receiver.h>

#define TIME_STEP 32
#define SIZE_OF_POP 30

WbNodeRef robot_node;
WbFieldRef trans_field;
WbFieldRef rot_field;

const double initial[3] = {0, 0.333583, 0};
const double initial_rot[4] = {0, 1, 0, 0};

typedef struct chromosome
{
  double imin[7];           // минимальные значения для параметров индивида
  double imax[7];           // максимальные значения для параметров индивида
  double defaultValues[7];  // значения по умолчанию параметров индивида
  double individ[7];        // параметры индивида
  double fitness;           // значение фитнес-функции
} chromosome;

void robot_to_init_pos();

void run_robot();

// Инициализация хромосомы
void chromosome_init(chromosome*);

/* 
    Метод, реализующий создание новой хромосомы чтобы значение каждого 
    из пяти параметров отличалось от значения по умолчанию на небольшую 
    случайную величину, и при этом попадало в интервал между минимальным 
    и максимальным допустимым значением
*/
void createIndividFromDefault(chromosome*);

// Метод, реализующий механизм арифмитического скрещивания
void crossover_arif(chromosome, chromosome, chromosome*, chromosome*);

// Метод, реализующий механизм смешанного скрещивания
void crossover_blx(chromosome, chromosome, chromosome*);

// Мутация
void mutation(chromosome*);

// Фитнес
double fitnessCulc();

void robot_to_init_pos()
{
  // reset robot position
  wb_supervisor_field_set_sf_vec3f(trans_field, initial);
  wb_supervisor_field_set_sf_rotation(rot_field, initial_rot);
  wb_supervisor_simulation_physics_reset();
}

void chromosome_init(chromosome* chromosome_to_init)
{
  chromosome_to_init->imin[0] = 0;
  chromosome_to_init->imax[0] = 0.3;
  chromosome_to_init->defaultValues[0] = 0.1;
  
  chromosome_to_init->imin[1] = 0.1;
  chromosome_to_init->imax[1] = 0.3;
  chromosome_to_init->defaultValues[1] = 0.1;
  
  chromosome_to_init->imin[2] = 0;
  chromosome_to_init->imax[2] = 0.4;
  chromosome_to_init->defaultValues[2] = 0.15;
  
  chromosome_to_init->imin[3] = 1;
  chromosome_to_init->imax[3] = 2;
  chromosome_to_init->defaultValues[3] = 1;
  
  chromosome_to_init->imin[4] = 1;
  chromosome_to_init->imax[4] = 6;
  chromosome_to_init->defaultValues[4] = 1;
  
  chromosome_to_init->imin[5] = 0;
  chromosome_to_init->imax[5] = 0.3;
  chromosome_to_init->defaultValues[5] = 0.1;
  
  chromosome_to_init->imin[6] = 0;
  chromosome_to_init->imax[6] = 0.3;
  chromosome_to_init->defaultValues[6] = 0.1;
}

void createIndividFromDefault(chromosome* chromosome_to_create)
{
int i;
  for (i=0; i<7; i++)
  {
    rand(); // 
    chromosome_to_create->individ[i] = (double)rand() 
                                        / (RAND_MAX + 1) 
                                        * (chromosome_to_create->imax[i] 
                                        - chromosome_to_create->imin[i]) 
                                        + chromosome_to_create->imin[i];
                                        
  } 
}

void crossover_arif(chromosome individ1_in, chromosome individ2_in, 
                    chromosome* individ1_out, chromosome* individ2_out)
{
  double cmin = 0;
  double cmax = 1;
  double m;
  
  int i;
  
  rand();
  m = (double)rand() / (RAND_MAX + 1) * (cmax - cmin) + cmin;
  
  for (i=0; i<7; i++)
  {
    individ1_out->individ[i] = m * individ1_in.individ[i] + (1 - m)*individ2_in.individ[i];
    individ2_out->individ[i] = m * individ2_in.individ[i] + (1 - m)*individ1_in.individ[i];
  }
}

void crossover_blx(chromosome individ1_in, chromosome individ2_in,
                                chromosome* individ1_out)
{
  double alfa = 0.5;
  double I;
  double cmin;
  double cmax;
  double fmin;
  double fmax;
  double h;
  
  int i;
  
  for (i=0; i<7; i++)
  {
    if (individ1_in.individ[i] < individ2_in.individ[i])
    {
      cmin = individ1_in.individ[i];
      cmax = individ2_in.individ[i];
    }
    else 
    {
        cmin = individ2_in.individ[i];
        cmax = individ1_in.individ[i];
    }

    I = cmax - cmin;
    fmin = cmin - alfa*I;
    fmax = cmax + alfa*I;
    
    rand();
    h = (double)rand() / (RAND_MAX + 1) * (fmax - fmin) + fmin;
    
    individ1_out->individ[i] = h;
  }
}

void mutation(chromosome* individ)
{
  int what_to_mutate;
  
  double nu;
  
  rand();
  what_to_mutate = rand()%6;
  
  rand();
  nu = (double)rand()/(double)RAND_MAX*(0.25+0.25)-0.25;
  
  individ->individ[what_to_mutate] += nu*(individ->imax[what_to_mutate]
                                    -individ->imin[what_to_mutate]);
}

double fitnessCulc()
{
  double dist;
  
  // compute travelled distance
  const double *pos = wb_supervisor_field_get_sf_vec3f(trans_field);
  dist = pos[2]-initial[2];
  printf("\nFIT");
  printf("\n%g", dist);
  return dist;
}

void selection()
{
  
}

void sort_popul(chromosome* popul)
{
  int i,j;
  chromosome temp;
  
  for (j=0; j<SIZE_OF_POP-1; j++)
  {
    for (i=0; i<SIZE_OF_POP-1; i++)
    {
      if (popul[i].fitness < popul[i+1].fitness)
      {
        temp = popul[i];
        popul[i] = popul[i+1];
        popul[i+1] = temp;
      }
    }
  }
}

int main() 
{
  wb_robot_init();
  
  // координаты робота
  robot_node = wb_supervisor_node_get_from_def("robot");
  trans_field = wb_supervisor_node_get_field(robot_node, "translation");
  rot_field = wb_supervisor_node_get_field(robot_node, "rotation");
  
  srand(time(NULL));
  
    
  int i, j, god, temp;
  
  double message[7];
  
  char* mail;
  
  chromosome popul[SIZE_OF_POP];
  chromosome temp_popul[SIZE_OF_POP];
  
  WbDeviceTag emit = wb_robot_get_device("emitter");
  
  WbDeviceTag receiver = wb_robot_get_device("receiver");
  wb_receiver_enable(receiver, TIME_STEP);
    
  // создаем первую популяцию
  
  for (i = 0; i < SIZE_OF_POP; i++)
  {
    chromosome_init(&popul[i]);
    createIndividFromDefault(&popul[i]);
    
    chromosome_init(&temp_popul[i]);
    createIndividFromDefault(&temp_popul[i]);
  }
  
  // мутируем каждую особь кроме первой 
  for (i = 1; i < SIZE_OF_POP; i++)
  {
    mutation(&popul[i]);
    //printf("\n%g", popul[i].individ[0]);
  }

 for (; ;)
 {
    //  посылаем контроллеру популяцию для симуляции
    for (i = 0; i < SIZE_OF_POP; i++)
    {
      printf("\n!!!");
      // посылаем контроллеру особь для симуляции
      for (j=0;j<7;j++)
      {
        
        message[j] = popul[i].individ[j];
        printf("\n%g", message[j]);
        
      }
      printf("\n???");
      wb_emitter_send(emit, message, 7*sizeof(double));
      //printf("\n%g", message[0]);
      
      while (1)
      {
        wb_robot_step(TIME_STEP);
        const char *messagechar = wb_receiver_get_data(receiver);
        if (wb_receiver_get_queue_length(receiver)>0)
        {
          //printf("\n%s", messagechar);
          if (strcmp(messagechar, "fin") == 0)
          {
            // вычисляем фитнесс
            popul[i].fitness = fitnessCulc();
            //printf("\n%g", popul[i].fitness);
            wb_receiver_next_packet(receiver);
            break;
          }
        } // если что-то получили
        wb_receiver_next_packet(receiver);
      } // ожидание завершения экспериментa
      robot_to_init_pos();
      wb_robot_step(TIME_STEP);
      mail = "next";
      //printf("\n%s", mail);
      wb_emitter_send(emit, mail, strlen(mail)+1);
    }
  
    printf("\nSORT\n");
    sort_popul(popul);
    for (temp=0;temp<30;temp++)
      printf("%g", popul[temp].fitness);
    printf("\nSORT\n");  
    
    for (temp=0; temp<6; temp++)
    {
      temp_popul[temp] = popul[temp];
      /*
      temp_popul[temp].fitness =  popul[temp].fitness;
      
      int k;
      for (k=0;k<7;k++)
      {
        temp_popul[temp].individ[k] = popul[temp].individ[k];
      }
      */
    }
    
    for (temp=6; temp<20; temp+=2)
    {
      rand();
      int first = rand()%9;
      int second = rand()%9;
      
      crossover_arif(popul[first],popul[second],&temp_popul[temp], &temp_popul[temp+1]);
    }
    
    for (temp=20; temp<25; temp++)
    {
      rand();
      int first = rand()%9;
      int second = rand()%9;
      
      crossover_blx(popul[first],popul[second],&temp_popul[temp]);
    }
    
    for (temp=25; temp<30; temp++)
    {
      rand();
      int what = rand()%9;
      
      temp_popul[temp] = popul[what];
      /*
      int k;
      for (k=0;k<7;k++)
      {
        temp_popul[temp].individ[k] = popul[temp].individ[k];
      }
      */
      mutation(&temp_popul[temp]);
    }
    
    for (temp=0; temp<30; temp++)
    {
      popul[temp] = temp_popul[temp];
      
      /*
      int k;
      for (k=0;k<7;k++)
      {
        popul[temp].individ[k] = temp_popul[temp].individ[k];
      }
      */
      printf("%g", popul[temp].individ[0]);
    }
    
    printf("\n");
  }
  
  wb_robot_cleanup();
  
  return 0;
}
