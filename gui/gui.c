/* gui.c */

#include "gui.h"
#include "../logic/logic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_SIZE 500
#define GRID_SIZE 4
#define TILE_SIZE 100

// глобальные переменные SDL
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;


// инициализация
int gui_init() {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {  // ИСПРАВЛЕНО: проверка ошибок TTF
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return 1;
    }

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
    -1, // любой драйвер
    SDL_RENDERER_ACCELERATED // использование видеокарты
  );
  font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 32); 
  if (!font) {
    printf("TTF_OpenFont Error: %s\n", TTF_GetError());  // ИСПРАВЛЕНО: вывод ошибки если шрифт не найден
    return 1;
  }
  return 0;
}

//рисовка плиток
void draw_tile(int value, int x, int y) {
  SDL_Rect rect = { x, y, TILE_SIZE - 10, TILE_SIZE - 10 };

  rect.x = x;
  rect.y = y;
  rect.w = TILE_SIZE - 10;
  rect.h = TILE_SIZE - 10;

  // Цвет плитки
  if (value == 0) {
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
  } else {
    SDL_SetRenderDrawColor(renderer, 255, 180, 0, 255);
  }

  // рисуем прямоугольник
  SDL_RenderFillRect(renderer,&rect);

  // Рисуем число
  if (value != 0 && font != NULL) {
    char text[6];
    sprintf(text, "%d", value);
    SDL_Color color = { 0, 0, 0, 255 }; 
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst;
    dst.w = surface->w;
    dst.h = surface->h;
    dst.x = x + (TILE_SIZE - dst.w) / 2 - 5;
    dst.y = y + (TILE_SIZE - dst.h) / 2 - 5;
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
  }
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

// обработка ввода
int gui_handle_input(int pole[4][4]) {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)) { 
    if(event.type == SDL_QUIT)
    return 0;
    if(event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym)
      {
        case SDLK_UP:
        moveTop(pole);
        break;

        case SDLK_DOWN:
        moveBottom(pole);
        break;
        
        case SDLK_LEFT:
        moveLeft(pole);
        break;
        
        case SDLK_RIGHT:
        moveRight(pole);
        break;
      }
    }
  }
  
  return 1;
}

// закрытие графики
void gui_destroy() {
  if (font) TTF_CloseFont(font);
  TTF_Quit();

  if (renderer) SDL_DestroyRenderer(renderer);
  if (window) SDL_DestroyWindow(window);

  SDL_Quit();
}




