/* gui.c */

#include "gui.h"
#include "../logic/logic.h"
#include <stdbool.h>

#defined WINDOW_SIZE 500
#defined GRID_SIZE 4
#defined TITLE_SIZE 100

// глобальные переменные SDL
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


int gui_init() {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow(
    "2048", // название окна
    SDL_WINDOWPOS_CENTERED, // позиция х
    SDL_WINDOWPOS_CENTERED, // позиция у
    WINDOW_SIZE, // ширина
    WINDOW_SIZE,  // высота
    0 //флаги
  );

  renderer = SDL_CreateRenderer(
    window,  // окно
    -1; // любой драйвер
    SDL_RENDERER_ACCELERATED; // использование видеокарты
  );
  return 0;
}



