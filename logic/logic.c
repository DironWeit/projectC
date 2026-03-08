/* logic.c */

#include <stdio.h>

int clearPole(int pole[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      pole[i][j] = 0;
    }
  }
  return 0;
}

int pokazPole(int pole[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d |", pole[i][j]);
    }
    printf("\n");
  }
}

