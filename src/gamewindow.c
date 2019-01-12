#include "gamewindow.h"

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

// Get input

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
