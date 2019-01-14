// this file contains functions that change player states
#include "player.h"

void player_update(struct Player *self){

if (self->xPos >=600)
  self->xPos = 600;
if (self->xPos <= 1)
  self->xPos = 1;

  if (self->yPos < 100)
    self->yPos = 100;


  if (self->yPos > 48)
    self->dY -= 2;

}

void player_jump(struct Player *self){
  self->yPos += 96;

}
