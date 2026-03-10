/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "logic/logic.h"

int main() {
  srand(time(NULL));
  //Инициализируем матрицу для поля 
  printf("Создаем поле\n");
  int pole[4][4] = {
  {0,0,0,2},
  {0,8,0,2},
  {0,0,2,0},
  {0,4,0,4}
  };
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Движение вправо\n");
  moveRight(pole);
  printf("Вывод\n");
  pokazPole(pole);
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Движение вверх\n");
  moveTop(pole);
  printf("Вывод\n");
  pokazPole(pole);
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Движение вправо\n");
  moveRight(pole);
  printf("Вывод\n");
  pokazPole(pole);
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Жвижение вниз\n");
  moveBottom(pole);
  printf("Вывод\n");
  pokazPole(pole);
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Движение влево\n");
  moveLeft(pole);  
  printf("Вывод\n");
  pokazPole(pole);
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Движение вправо\n");
  moveRight(pole);
  printf("Вывод\n");
  pokazPole(pole);
  
  printf("Содается случайный элемент\n");
  addRandTitle(pole);
  printf("Вывод\n");
  pokazPole(pole);
  printf("Движение вправо\n");
  moveRight(pole);
  printf("Вывод\n");
  pokazPole(pole);



  return 0;
}
