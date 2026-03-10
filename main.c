/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "logic/logic.h"

int main() {
  srand(time(NULL));
  //Инициализируем матрицу для поля 
  int pole[4][4] = {
  {0,2,0,2},
  {0,0,0,2},
  {0,2,2,2},
  {2,4,0,4}
  };
  printf("до переворода на 90 градусов по часовой\n");
  pokazPole(pole);
  printf("После переворода на 90 градусов по часовой\n");
  roteteMatrix(pole);
  pokazPole(pole);
  printf("После переворода на -90 градусов по часовой\n");
  unRoteteMatrix(pole);
  pokazPole(pole);
  
  
  

  

  return 0;
}
