/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "logic/logic.h"

int main() {
  srand(time(NULL));
  //Инициализируем матрицу для поля 
  int pole[4][4];
  //Очистим матрицу до начальных значений
  clearPole(pole);
  pokazPole(pole);
  printf("---\n");
  addRandTitle(pole);
  pokazPole(pole);

  

  

  return 0;
}
