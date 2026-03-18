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
  switch (value) {
    case 0:   SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255); break;
    case 2:   SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255); break;
    case 4:   SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255); break;
    case 8:   SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255); break;
    case 16:  SDL_SetRenderDrawColor(renderer, 245, 149, 99, 255); break;
    case 32:  SDL_SetRenderDrawColor(renderer, 246, 124, 95, 255); break;
    case 64:  SDL_SetRenderDrawColor(renderer, 246, 94, 59, 255); break;
    case 128: SDL_SetRenderDrawColor(renderer, 237, 207, 114, 255); break;
    case 256: SDL_SetRenderDrawColor(renderer, 237, 204, 97, 255); break;
    case 512: SDL_SetRenderDrawColor(renderer, 237, 200, 80, 255); break;
    case 1024:SDL_SetRenderDrawColor(renderer, 237, 197, 63, 255); break;
    case 2048:SDL_SetRenderDrawColor(renderer, 237, 194, 46, 255); break;
    default:  SDL_SetRenderDrawColor(renderer, 60, 58, 50, 255); break; // для больших чисел
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

void gui_draw(int pole[4][4], int score){
  SDL_SetRenderDrawColor(renderer,220,220,220,255);
  SDL_RenderClear(renderer);

  for(int i=0;i<GRID_SIZE;i++){
    for(int j=0;j<GRID_SIZE;j++){
      int x = j*TILE_SIZE + 50;
      int y = i*TILE_SIZE + 50;
        
      draw_tile(pole[i][j],x,y);
    }
  }

  char score_text[32];
  sprintf(score_text, "Score: %d", score);
  SDL_Color color = {0,0,0,255};
  SDL_Surface* surface = TTF_RenderText_Blended(font, score_text, color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  
  SDL_Rect dst;
  dst.x = 10;
  dst.y = 10;
  dst.w = surface->w;
  dst.h = surface->h;

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  SDL_RenderPresent(renderer);
}

// обработка ввода
int gui_handle_input(int pole[4][4], int *score) {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)) { 
    if(event.type == SDL_QUIT)
    return 0;
    if(event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym)
      {
        case SDLK_UP:
        moveTop(pole, score);
        break;

        case SDLK_DOWN:
        moveBottom(pole, score);
        break;
        
        case SDLK_LEFT:
        moveLeft(pole, score);
        break;
        
        case SDLK_RIGHT:
        moveRight(pole, score);
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




