#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
typedef struct
{
  int x,y;
  short life;
  float dy;
  char *name;

} Gumba;
typedef struct{
  int x,y,w,h;
}Block;

typedef struct
{
  Gumba a;
  Block block[100];
  SDL_Texture *boden;
  SDL_Texture *gumba;

}GameState;

int processEvent(SDL_Window *win, GameState *game)
{
  SDL_Event event;
  int done = 0;

  while(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      done = 1;
      break;

 }
 const Uint8 *state = SDL_GetKeyboardState(NULL);
 if(state[SDL_SCANCODE_A]){
   game->a.x--;
 }
 if(state[SDL_SCANCODE_D]){
   game->a.x++;
 }
 if(state[SDL_SCANCODE_W]){
   game-> a.y--;
 }
 if(state[SDL_SCANCODE_S]){
   game->a.y++;
 }

}

  return done;
}

void doRender(SDL_Renderer *rend, GameState *game)
{
  SDL_SetRenderDrawColor(rend, 0,0,25,255);
  SDL_RenderClear(rend);
  SDL_SetRenderDrawColor(rend, 255,255,48,48);

  SDL_Rect gumbaRect = {game->a.x, game->a.y,48,48};
  SDL_RenderCopy(rend, game->gumba,NULL, &gumbaRect);




  SDL_Rect bodenRect = {1,430,48,48};
  SDL_RenderCopy(rend, game->boden,NULL,&bodenRect);
  for (int i= 0;i < 15;i++) {
    game->block[i].w= 48;
    game->block[i].h = 48;
    game->block[i].x = i*48;
    game ->block[i].y = 430;

  }
  for(int i =0; i <15; i++)
  {
  SDL_Rect blockrect = {game->block[i].x, game->block[i].y,game->block[i].w, game->block[i].h};
  SDL_RenderCopy(rend, game->boden,NULL, &blockrect);
}

  SDL_RenderPresent(rend);
}
//void process(GameState *game)
//{
  //Gumba a = game->a;
  //a->y += a ->dy;
//}

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
int main(void)
{
    GameState gameState;
    gameState.a.x = 220;
    gameState.a.y = 140;
    SDL_Surface *bodenSurface = NULL;
    SDL_Surface *gumbaSurface = NULL;


    SDL_Window* win = SDL_CreateWindow("Super Friedolin",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480, 0);


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

    //collisionDetect(&gameState);

     doRender(rend, &gameState);
     SDL_Delay(1000/60);
   }
    SDL_DestroyTexture(gameState.gumba);
    SDL_DestroyTexture(gameState.boden);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
