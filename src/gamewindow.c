#include "gamewindow.h"

void doRender(SDL_Renderer *rend, int x, int y, int width, int height, SDL_Texture *tex)
{

  SDL_Rect rect = {x,SCREEN_HEIGHT-y,width,height};
  SDL_RenderCopy(rend, tex, NULL, &rect);

  // SDL_Rect rect = {x, y,48,48};
  // SDL_RenderCopy(rend, game->gumba,NULL, &rect);

  // SDL_Rect bodenRect = {1,430,48,48};
  // SDL_RenderCopy(rend, game->boden,NULL,&bodenRect);
  // for (int i= 0;i < 15;i++) {
  //   game->block[i].w= 48;
  //   game->block[i].h = 48;
  //   game->block[i].x = i*48;
  //   game ->block[i].y = 430;
  //}

  // for(int i =0; i <15; i++){
  //   SDL_Rect blockrect = {game->block[i].x, game->block[i].y,game->block[i].w, game->block[i].h};
  //   SDL_RenderCopy(rend, game->boden,NULL, &blockrect);
  // }

  //SDL_RenderPresent(rend);
}
//void process(GameState *game)
//{
  //Gumba a = game->a;
  //a->y += a ->dy;
//}
void background_update(struct Background *self){
  if (self->xPos <= (-2*SCREEN_WIDTH))
    self->xPos = SCREEN_WIDTH;
}
