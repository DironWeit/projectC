/* logic.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

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
    printf("|");
    for (int j = 0; j < 4; j++) {
      printf("%d|", pole[i][j]);
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

//Функция сортировки в рамке 1 строки
//дублирует строку
//сдвигает все нули вправо
//копирует дуюлированную строку в наш основной массив
int sortStr(int i, int pole[4][4]) {
  int tmpStr[4] = {0};
  bool entSt = false;
  for (int j =0; j < 4; j++) {
    tmpStr[j] = pole[i][j];
  }

  while (entSt != true) {
    entSt = true;
    for (int k =0; k <3;k++) {
      if (tmpStr[k] == 0 && tmpStr[k+1] !=0) {
        tmpStr[k] = tmpStr[k+1];
        tmpStr[k+1] = 0;
        entSt = false;
      }
    }
  }

  for (int r =0; r < 4; r++) {
     pole[i][r] = tmpStr[r];
  }
  return 0;
}

//Функция суммирования соседних элементов в 1 строке
//копирует строку
//находит равных соседниъ элементов и их суммирует со сдвигом в лево
//переносит дублированную строку в основной массив
int sumStr(int i, int pole[4][4]) {
  int tmpStr[4] = {0};
  bool entSt = false;
  for (int j = 0; j <4;j++) {
    tmpStr[j] = pole[i][j];
  }

  for (int k = 0; k <3;k++) {
    if (tmpStr[k] == tmpStr[k+1]) {
      tmpStr[k] = tmpStr[k]*2;
      tmpStr[k+1] = 0;
      k++;
    }
  }

  for (int r =0; r < 4; r++) {
    pole[i][r] = tmpStr[r];
  }
  return 0;
}

//движение влево
//управлеяет подвункциями
int dvish(int pole[4][4]) {
  int i = 0;
  while (i < 4){
    sortStr(i, pole);
    sumStr(i, pole);
    sortStr(i, pole);
    i++;
  }
}

//Функция повораьта матрици для того что бы не делать много функций сдвигов
//Работа цункции:
//Идем по стр снизу и строки выставляем в столбец
int roteteMatrix(int pole[4][4]) {
  int tempMatrix[4][4] = {0};
  for (int i = 0; i < 4; i++) {
    for (int j =0; j <4;j++) {
      tempMatrix[j][3 - i] = pole[i][j];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      pole[i][j] = tempMatrix[i][j];
    }
  }
}

//Функция поворота матрици в обратную сторану 
int unRoteteMatrix(int pole[4][4]) {
  int tempMatrix[4][4] = {0};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tempMatrix[3 - j][i] = pole[i][j];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      pole[i][j] = tempMatrix[i][j];
    }
  }
}

int moveLeft(int pole[4][4]) {
  dvish(pole);
}

int moveRight(int pole[4][4]) {
  roteteMatrix(pole);
  roteteMatrix(pole);
  dvish(pole);
  unRoteteMatrix(pole);
  unRoteteMatrix(pole);
}

int moveTop(int pole[4][4]) {
  unRoteteMatrix(pole);
  dvish(pole);
  roteteMatrix(pole);
}

int moveBottom(int pole[4][4]) {
  roteteMatrix(pole);
  dvish(pole);
  unRoteteMatrix(pole);
}


