#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "game.h"

#define SCREEN_NAME "Super Friedolin Go Pikachu(TM)"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 0

// Function prototypes



void doRender(SDL_Renderer *rend, int x, int y, SDL_Texture *tex);
