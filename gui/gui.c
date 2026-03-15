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


// инициализация
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

//рисовка плиток
void draw_tile(int value, int x, int y) {
  SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = TILE_SIZE - 10;
  rect.h = TILE_SIZE - 10;

  // Цвет плитки
  if(value == 0) {
    SDL_SetRenderDrawColor(renderer,180,180,180,255);
  } else {
    SDL_SetRenderDrawColor(renderer,255,180,0,255);
  }

  // рисуем прямоугольник
  SDL_RenderFillRect(renderer,&rect);
}

void gui_draw(int pole[4][4]){
  SDL_SetRenderDrawColor(renderer,220,220,220,255);
  SDL_RenderClear(renderer);

  for(int i=0;i<GRID_SIZE;i++){
    for(int j=0;j<GRID_SIZE;j++){
      int x = j*TILE_SIZE + 50;
      int y = i*TILE_SIZE + 50;
        
      draw_tile(pole[i][j],x,y);
    }
  }
  SDL_RenderPresent(renderer);
}






