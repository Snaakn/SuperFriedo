#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "game.h"

#define SCREEN_NAME "Super Friedolin Go Pikachu(TM)"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_SCALE 0
#define TILE_SIZE 100
#define GAMESPEED (TILE_SIZE/50)


struct Background{
  int xPos;
  void (*update)(struct Background *);
};


// Function prototypes
void doRender(SDL_Renderer *rend, int x, int y, int width, int height, SDL_Texture *tex);
void background_update(struct Background *);
