#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "logic/logic.h"
#include "gui/gui.h"

static void get_today(char* out, size_t out_size) {
  time_t t = time(NULL);
  struct tm* lt = localtime(&t);
  if (!lt) {
    if (out_size > 0) out[0] = '\0';
    return;
  }
  strftime(out, out_size, "%Y-%m-%d", lt);
}

static int load_best_score(const char* path, char* best_date, size_t best_date_size) {
  FILE* f = fopen(path, "r");
  if (!f) {
    if (best_date_size > 0) best_date[0] = '\0';
    return 0;
  }
  int v = 0;
  char date_buf[32] = {0};
  int n = fscanf(f, "%d %31s", &v, date_buf);
  if (n < 1) v = 0;
  if (best_date_size > 0) {
    if (n >= 2) {
      strncpy(best_date, date_buf, best_date_size - 1);
      best_date[best_date_size - 1] = '\0';
    } else {
      best_date[0] = '\0';
    }
  }
  fclose(f);
  return v;
}

static void save_best_score(const char* path, int v, const char* best_date) {
  FILE* f = fopen(path, "w");
  if (!f) return;
  if (best_date && best_date[0] != '\0') {
    fprintf(f, "%d %s", v, best_date);
  } else {
    fprintf(f, "%d", v);
  }
  fclose(f);
}

int main() {
  srand(time(NULL));
  int pole[4][4] = {0};
  int score = 0; 
  int show_lost = 0;
  int lost_score = 0;

  const char* BEST_PATH = "best_score.txt";
  char best_date[16] = {0};
  int best_score = load_best_score(BEST_PATH, best_date, sizeof(best_date));
  
  addRandTitle(pole);
  addRandTitle(pole);

  gui_init();

  int running = 1;

  while (running) {
    running = gui_handle_input(pole, &score, &show_lost);
    if (score > best_score) {
      best_score = score;
      get_today(best_date, sizeof(best_date));
      save_best_score(BEST_PATH, best_score, best_date);
    }
    if (!show_lost && gameIsOver(pole)) {
      lost_score = score;
      show_lost = 1;
      clearPole(pole);
      addRandTitle(pole);
      addRandTitle(pole);
      score = 0;
    }
    gui_draw(pole, score, best_score, best_date, show_lost, lost_score);
  }

  
  gui_destroy();
  return 0;
}
