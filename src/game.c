#include "stdio.h"
#include "gamewindow.h"

//-------------------------------------------------------------------------

 void collisionDetect (GameState *game)
 {
   for (int i  = 0; i < 15; i++) {
     float mw = 40, mh = 40;
     float mx = game->a.x;
     float my = game->a.y;
     float bx = game->block[i].x, by = game->block[i].y, bw = game->block[i].h, bh = game ->block[i].w;
    if(my+mh > by && my < by+bh)
    {
      if (mx < bx+bw && mx+mw > bx+bw)
      {
        game->a.x = bx+bw;
        mx = bx+bw;
      }else if (mx +mw > bx && mx < bx)
      {
        game -> a.x = bx-mw;
        mx = bx-mw;
      }
    }
    if(mx+mw > bx && mx<bx+bw){
      if(my < by+bh && my > by){
        game->a.y = by+bh;
      }

    }if (my+mh > by && my < by)
    {
      game->a.y = by-mh;

    }
  }

 }


//---------------------------MAIN-------------------------------------------
int main(void)
{
    GameState gameState;
    gameState.a.x = 220;
    gameState.a.y = 140;
    SDL_Surface *bodenSurface = NULL;
    SDL_Surface *gumbaSurface = NULL;


    SDL_Window* win = SDL_CreateWindow(SCREEN_NAME,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE);


    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);


   bodenSurface = IMG_Load("Images/boden.png");
   gameState.boden = SDL_CreateTextureFromSurface(rend, bodenSurface);
   SDL_FreeSurface(bodenSurface);
   gumbaSurface = IMG_Load("Images/gumba.png");
   gameState.gumba = SDL_CreateTextureFromSurface(rend,gumbaSurface);
   SDL_FreeSurface(gumbaSurface);



   int done = 0;

   while(!done){
    if(processEvent(win, &gameState) == 1)
    done =1;
    // TODO iterate over level array and choose textures from chars in array

    //collisionDetect(&gameState);

     doRender(rend, &gameState);
     SDL_Delay(1000/60);
   }
    SDL_DestroyTexture(gameState.gumba);
    SDL_DestroyTexture(gameState.boden);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
