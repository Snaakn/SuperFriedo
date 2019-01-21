#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "game.h"

#define SCREEN_NAME "Super Friedolin Go Pikachu(TM)"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_SCALE 0
#define TILE_SIZE 48

// Function prototypes
void doRender(SDL_Renderer *rend, int x, int y, SDL_Texture *tex);
