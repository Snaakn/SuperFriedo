// this file contains functions that change player states
#include "player.h"


void player_update(struct Player *self, struct Cam *camera, char *lvl_arr, struct Level *level){
  if (self->xPos >=camera->xPos+SCREEN_WIDTH)
    self->xPos = camera->xPos+SCREEN_WIDTH;
  if (self->xPos <= camera->xPos)
    self->xPos = camera->xPos;

    if (self->yPos <= 0){
      self->lives--;
      self-> yPos = SCREEN_HEIGHT;
      self->xPos = camera->xPos+(self->lives*TILE_SIZE);
      printf("One life lost\n");
    }

    if (self->dY > -8*GAMESPEED)
      self->dY -= 2*GAMESPEED;
      // gravity
    if (!collision(self->xPos, self->yPos, 0, self->dY, lvl_arr, level)){
      self->canjump = 0;
      self->yPos += self->dY;
    }
    else {
      self->canjump=1;
      self->yPos -= self->yPos%TILE_SIZE;
    }
}

void player_jump(struct Player *self){
  if(self->canjump){
    self->dY =26*GAMESPEED;
    self->canjump=0;
  }
}
