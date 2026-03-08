/* main.c */

#include <stdio.h>
#include "logic/logic.h"

int main() {
  int pole[4][4];
  printf("Поле созданно:\n");
  pokazPole(pole);
  printf("Поле очищенно:\n");
  clearPole(pole);
  pokazPole(pole);


  return 0;
}
