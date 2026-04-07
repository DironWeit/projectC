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

    if (TTF_Init() == -1) {  
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
  font = TTF_OpenFont("arial.ttf", 32); 
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
    case 0:
      SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
      break;
    case 2:
      SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255);
      break;
    case 4:
      SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255);
      break;
    case 8:
      SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255);
      break;
    case 16:
      SDL_SetRenderDrawColor(renderer, 245, 149, 99, 255);
      break;
    case 32:
      SDL_SetRenderDrawColor(renderer, 246, 124, 95, 255);
      break;
    case 64:
      SDL_SetRenderDrawColor(renderer, 246, 94, 59, 255);
      break;
    case 128:
      SDL_SetRenderDrawColor(renderer, 237, 207, 114, 255);
      break;
    case 256:
      SDL_SetRenderDrawColor(renderer, 237, 204, 97, 255);
      break;
    case 512:
      SDL_SetRenderDrawColor(renderer, 237, 200, 80, 255);
      break;
    case 1024:
      SDL_SetRenderDrawColor(renderer, 237, 197, 63, 255);
      break;
    case 2048:
      SDL_SetRenderDrawColor(renderer, 237, 194, 46, 255);
      break;
    default:
      SDL_SetRenderDrawColor(renderer, 60, 58, 50, 255);
      break; // для больших чисел
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

void gui_draw(int pole[4][4], int score, int best_score, const char* best_date, int show_lost, int lost_score) {
  SDL_SetRenderDrawColor(renderer,220,220,220,255);
  SDL_RenderClear(renderer);

  for(int i=0; i<GRID_SIZE; i++){
    for(int j=0; j<GRID_SIZE; j++){
      int x = j*TILE_SIZE + 50;
      int y = i*TILE_SIZE + 90;
        
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

  char best_text[64];
  if (best_date && best_date[0] != '\0') {
    sprintf(best_text, "Best  : %d  %s", best_score, best_date);
  } else {
    sprintf(best_text, "Best  : %d", best_score);
  }
  SDL_Surface* surface2 = TTF_RenderText_Blended(font, best_text, color);
  SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

  SDL_Rect dst2;
  dst2.x = 10;
  dst2.y = dst.y + dst.h + 5; // ниже Score
  dst2.w = surface2->w;
  dst2.h = surface2->h;

  SDL_RenderCopy(renderer, texture2, NULL, &dst2);
  SDL_FreeSurface(surface2);
  SDL_DestroyTexture(texture2);



  if (show_lost) {
    char lost_text[64];
    sprintf(lost_text, "You lost: %d", lost_score);
    SDL_Color lost_color = {200, 0, 0, 255};

    SDL_Surface* surface3 = TTF_RenderText_Blended(font, lost_text, lost_color);
    SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);

    SDL_Rect dst3;
    dst3.x = 10;
    dst3.y = dst2.y + dst2.h + 5;
    dst3.w = surface3->w;
    dst3.h = surface3->h;

    SDL_RenderCopy(renderer, texture3, NULL, &dst3);
    SDL_FreeSurface(surface3);
    SDL_DestroyTexture(texture3);

    char hint_text[64] = "Press P to continue";
    SDL_Color hint_color = {0, 0, 0, 255};
    SDL_Surface* surface4 = TTF_RenderText_Blended(font, hint_text, hint_color);
    SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, surface4);

    SDL_Rect dst4;
    dst4.x = 10;
    dst4.y = dst3.y + dst3.h + 5;
    dst4.w = surface4->w;
    dst4.h = surface4->h;

    SDL_RenderCopy(renderer, texture4, NULL, &dst4);
    SDL_FreeSurface(surface4);
    SDL_DestroyTexture(texture4);
  }

  SDL_RenderPresent(renderer);
}

// обработка ввода
int gui_handle_input(int pole[4][4], int *score, int *show_lost) {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)) { 
    if(event.type == SDL_QUIT)
    return 0;
    if(event.type == SDL_KEYDOWN) {
      if (*show_lost) {
        if (event.key.keysym.sym == SDLK_p) {
          *show_lost = 0;
        }
        continue;
      }
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
  if (font) { 
    TTF_CloseFont(font);
  }
  TTF_Quit();

  if (renderer) 
    SDL_DestroyRenderer(renderer);
  if (window) 
    SDL_DestroyWindow(window);

  SDL_Quit();
}




