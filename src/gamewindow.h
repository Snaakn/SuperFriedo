#include "game.h"

#define SCREEN_NAME "Super Friedolin Go Pikachu(TM)"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 0

// Function prototypes
int processEvent(SDL_Window *win, GameState *game);
void doRender(SDL_Renderer *rend, GameState *game);
