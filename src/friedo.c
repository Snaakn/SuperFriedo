#include "stdio.h"
#include "stdlib.h"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "Super Friedolin Go Pikachu(TM)"

// -------------------------------------------
void game_init(void);
void game_quit(void);

static struct {
    // define attributes
    SDL_bool running;
    struct {
  		unsigned int width;
  		unsigned int height;
  		const char* title;
  		SDL_Window* window;
  		SDL_Renderer* renderer;
  	} screen;

    //define "methods"
    void (*init)(void);
    void (*quit)(void);
}Game = {
    SDL_FALSE,
    {
  		SCREEN_SCALE*SCREEN_WIDTH,
  		SCREEN_SCALE*SCREEN_HEIGHT,
  		SCREEN_NAME,
  		NULL,
  		NULL
	  },
    game_init,
    game_quit
  };

// -------------------------------------------
void game_init(void) {
  printf("game_init()\n");

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("SDL error -> %s\n", SDL_GetError());
    exit(1);
  }
  unsigned int width = Game.screen.width;
  unsigned int height = Game.screen.height;
  const char* title = Game.screen.title;

  Game.screen.window = SDL_CreateWindow(
    title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  Game.screen.renderer = SDL_CreateRenderer(
      Game.screen.window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

  Game.running = SDL_TRUE;
}

// -------------------------------------------
void game_quit(void) {
  SDL_DestroyRenderer(Game.screen.renderer);
  SDL_DestroyWindow(Game.screen.window);

  Game.screen.window = NULL;
  Game.screen.renderer = NULL;

  printf("game_quit()\n");
  SDL_Quit();
  Game.running = SDL_FALSE;
}

// -------------------------------------------
int main(int argc, char const *argv[]) {
  Game.init();

  SDL_Event event;
while(Game.running) {
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT: {
        Game.running = SDL_FALSE;
      } break;
    }
  }

  SDL_RenderClear(Game.screen.renderer);
  SDL_RenderPresent(Game.screen.renderer);
}

  printf("running = %d\n", Game.running);

  while (Game.running) {
    Game.quit();
  }

  printf("running = %d\n", Game.running);

  return 0;
}
