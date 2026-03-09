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
//функция рандома измененена на более рандомную
int addRandTitle(int pole[4][4]) {
  int i = rand() % 100;
  int j = rand() % 100;

  if (i >= 0 && i <25) {
    i = 1;
  } else if (i >= 25 && i < 50) {
    i = 2;
  } else if (i >=50 && i < 75) {
    i = 3;
  } else {
    i =4;
  }
  if (j >= 0 && j <25) {
    j = 1;
  } else if (j >= 25 && j < 50) {
    j = 2;
  } else if (j >=50 && j < 75) {
    j = 3;
  } else {
    j =4;
  }

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





