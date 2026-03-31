#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic/logic.h"
#include "gui/gui.h"

static int load_best_score(const char* path) {
  FILE* f = fopen(path, "r");
  if (!f) return 0;
  int v = 0;
  if (fscanf(f, "%d", &v) != 1) v = 0;
  fclose(f);
  return v;
}

static void save_best_score(const char* path, int v) {
  FILE* f = fopen(path, "w");
  if (!f) return;
  fprintf(f, "%d", v);
  fclose(f);
}

int main() {
  srand(time(NULL));
  int pole[4][4] = {0};
  int score = 0; 
  const char* BEST_PATH = "best_score.txt";
  int best_score = load_best_score(BEST_PATH);
  
  addRandTitle(pole);
  addRandTitle(pole);

  gui_init();

  int running = 1;

  while (running) {
    running = gui_handle_input(pole, &score);
    if (score > best_score) {
      best_score = score;
      save_best_score(BEST_PATH, best_score);
    }
    gui_draw(pole, score, best_score);
    if (gameIsOver(pole)) 
      running = 0;
  }
  
  gui_destroy();
  return 0;
}