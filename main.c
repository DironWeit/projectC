/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "logic/logic.h"

int main() {
  srand(time(NULL));
  //Инициализируем матрицу для поля 
  printf("Создаем поле\n");
  int pole[4][4] = {0};
  addRandTitle(pole);
  pokazPole(pole);

  // Тело игры
  while (!gameIsOver(pole)) {

  //Символы стрелок  в линукс это последовательность из 3 символов. 
  //Мы сначала проверяем на символ с кодом 27, потом на [ и после уже проверяем на опредленную стрелку
    // и вызываем что надо
    int key = my_getch();
    if (key == 27) {
      if (my_getch() == '[') {
        int arrow = my_getch();
        switch (arrow) {
          case 'A': moveTop(pole); break;    
          case 'B': moveBottom(pole); break; 
          case 'C': moveRight(pole); break;  
          case 'D': moveLeft(pole); break;   
        }
      }
    }
    
    //Считаем пустые клетки
    //очищаем экран
    //Выводим
    system("clear");
    pokazPole(pole);
    
    
  }
  printf("Game Over\n");
  return 0;
}
