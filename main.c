#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic/logic.h"
#include "gui/gui.h"

int main() {
  srand(time(NULL));
  int pole[4][4] = {0};
  int score = 0; 
  
  addRandTitle(pole);
  addRandTitle(pole);

  gui_init();

  int running = 1;

  while (running) {
    running = gui_handle_input(pole, &score);
    gui_draw(pole, score);
    if (gameIsOver(pole)) 
      running = 0;
  }
  
  gui_destroy();
  return 0;
}