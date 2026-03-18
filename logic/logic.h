/* logic.h */
#ifndef __LOGIC_H__
#define __LOGIC_H__
#include <stdbool.h>
int clearPole(int pole[4][4]);
int pokazPole(int pole[4][4]);
int addRandTitle(int pole[4][4]);

void dvish(int pole[4][4], int *score);
void roteteMatrix(int pole[4][4]);
void unRoteteMatrix(int pole[4][4]);

int moveLeft(int pole[4][4], int *score);
int moveRight(int pole[4][4], int *score);
int moveTop(int pole[4][4], int *score);
int moveBottom(int pole[4][4], int *score);

int check(int pole[4][4]);
int my_getch();

bool gameIsOver(int pole[4][4]);
#endif
