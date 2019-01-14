// this file contains functions that change player states
#include "player.h"

void player_update(struct Player *self){

  if (self->xPos >=600)
    self->xPos = 600;
    if (self->xPos <= 1)
      self->xPos = 1;

  // if (self->yPos < 100)
  //   self->yPos = 100;
  if (self->dY > -7)
    self->dY -= 7;
    if (self->dY < 0) {
      self->dY = -7;
    }

      self->yPos += (self->dY);

// will be changed when collision is working
      if (self->yPos < 48)
        self->yPos=48;
}

void player_jump(struct Player *self){
    self->dY = 70;
}
