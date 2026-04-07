/* logic.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>




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
  int col = 0;
  for (int i =0; i < 4; i++) {
    for (int j =0; j < 4; j++) {
      if (pole[i][j] == 0) {
        col++;
      }
    }
  }
  if (col == 0) {
    return 0;
  }

  int i = rand() % 100;
  int j = rand() % 100;

  if (i >= 0 && i <25) {
    i = 0;
  } else if (i >= 25 && i < 50) {
    i = 1;
  } else if (i >=50 && i < 75) {
    i = 2;
  } else {
    i =3;
  }
  if (j >= 0 && j <25) {
    j = 0;
  } else if (j >= 25 && j < 50) {
    j = 1;
  } else if (j >=50 && j < 75) {
    j = 2;
  } else {
    j =3;
  }

  int proc = rand() % 100 + 1;
  int num;
  while (pole[i][j] != 0) {
    i = rand() % 4;
    j = rand() % 4;
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
int sumStr(int i, int pole[4][4], int *score) {
  int tmpStr[4] = {0};
  bool entSt = false;
  for (int j = 0; j <4;j++) {
    tmpStr[j] = pole[i][j];
  }

  for (int k = 0; k < 3; k++) {
    if (tmpStr[k] == tmpStr[k+1]) {
      tmpStr[k] = tmpStr[k]*2;
      tmpStr[k+1] = 0;
      *score += tmpStr[k];
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
void dvish(int pole[4][4], int *score) {
  int i = 0;
  while (i < 4){
    sortStr(i, pole);
    sumStr(i, pole, score);
    sortStr(i, pole);
    i++;
  }
}

//Функция повораьта матрици для того что бы не делать много функций сдвигов
//Работа цункции:
//Идем по стр снизу и строки выставляем в столбец
void  roteteMatrix(int pole[4][4]) {
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
void  unRoteteMatrix(int pole[4][4]) {
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
// сравнение матриц
bool isChanged(int old[4][4], int pole[4][4]) {

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (old[i][j] != pole[i][j]) {
        return true;
      }
    }
  }

  return false;
}

// Движение лево
int moveLeft(int pole[4][4], int *score) {

  int old[4][4];

  // копируем поле
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      old[i][j] = pole[i][j];
    }
  }

  // выполняем движение
  dvish(pole, score);

  // проверяем изменилось ли поле
  bool changed = false;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (old[i][j] != pole[i][j]) {
        changed = true;
      }
    }
  }

  // если изменилось — добавляем плитку
  if (changed) {
    addRandTitle(pole);
  }

  return 0;
}
// Движение право
int moveRight(int pole[4][4], int *score) {

  int old[4][4];

  // копируем поле
  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      old[i][j] = pole[i][j];
    }
  }
  
  roteteMatrix(pole);
  roteteMatrix(pole);

  dvish(pole, score);

  unRoteteMatrix(pole);
  unRoteteMatrix(pole);

  if (isChanged(old, pole)) {
    addRandTitle(pole);
  }
}
// Движение верх
int moveTop(int pole[4][4], int *score) {

  int old[4][4];

  for (int i=0;i<4;i++)
    for (int j=0;j<4;j++)
      old[i][j] = pole[i][j];

  unRoteteMatrix(pole);
  dvish(pole, score);
  roteteMatrix(pole);

  if (isChanged(old, pole)) {
    addRandTitle(pole);
  }
}
// Движение низ
int moveBottom(int pole[4][4], int *score) {

  int old[4][4];

  for (int i=0;i<4;i++)
    for (int j=0;j<4;j++)
      old[i][j] = pole[i][j];

  roteteMatrix(pole);
  dvish(pole, score);
  unRoteteMatrix(pole);

  if (isChanged(old, pole)) {
    addRandTitle(pole);
  }
}

// Проверка на свободные клетки в игровом поле
int check(int pole[4][4]) {
  int s = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (pole[i][j] != 0) {
        s++;
      }
    }
  }
  return s;
}

// функция для ввода клавиш
int my_getch() {
    struct termios oldt, newt;
    int ch;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

//Большая функция проверки остался ли код
//Если осталось 0 пустых ячеек и эта функция вернет true тогда игра законченна  
// Переработал
bool gameIsOver(int pole[4][4]) {

    // если есть пустая клетка — игра продолжается
    for (int i=0;i<4;i++){
      for (int j=0;j<4;j++){
        if (pole[i][j] == 0)
          return false;
      }
    }

    // проверка горизонтали
    for (int i=0;i<4;i++){
      for (int j=0;j<3;j++){
        if (pole[i][j] == pole[i][j+1])
          return false;
      }
    }

    // проверка вертикали
    for (int j=0;j<4;j++){
      for (int i=0;i<3;i++){
        if (pole[i][j] == pole[i+1][j])
          return false;
      }
    }

    return true;
}


