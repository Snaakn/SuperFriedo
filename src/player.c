// this file contains functions that change player states
#include "player.h"


void player_update(struct Player *self){
  if (self->xPos >=600)
    self->xPos = 600;
  if (self->xPos <= 1)
    self->xPos = 1;

    if (self->yPos < 100)
      self->yPos = 100;

    if (self->dY > -8)
      self->dY -= 2;
      // gravity
    if (self->yPos > 48)
      self->yPos += self->dY;
      // walk 
     self->xPos += self->dX;
     
    // if (self->dX > 0)
    //   self->dX-= 1;
    // if(self->dX < 0)
    //   self->dX+= 1;
}

void player_jump(struct Player *self){
  if(self->yPos < 110)
    self->dY =20;

}
