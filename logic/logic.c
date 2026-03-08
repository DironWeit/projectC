/* logic.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Функция очистки всего поля
//берем каждую клетку матриции и присваем ей 0
int clearPole(int pole[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      pole[i][j] = 0;
    }
  }
  return 0;
}

//Функция вывода матрици в терминал 
//берем каждую клетку в строке и выводи, а после прохождения строки переносим коретку
int pokazPole(int pole[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d |", pole[i][j]);
    }
    printf("\n");
  }
}


//Функция подстановки 2 или 4 в случайную клетку
//инициализируем переменные и рандомные числа
//если число процента юольше 90 то подставим число 4, если нет, то 2
//и заполним нужную клетку числои
int addRandTitle(int pole[4][4]) {
  int i = rand() % 3 + 0;
  int j = rand() % 3 + 0;
  int proc = rand() % 100 + 1;
  int num;
  if (pole[i][j] != 0) {
    return addRandTitle(pole);
  }
  

  if (proc >=90) {
    num = 4;
  } else {
    num = 2;
  }
  pole[i][j] = num;
  return 0;
}



