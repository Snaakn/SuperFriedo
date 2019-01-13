// this file contains functions that change player states
#include "player.h"

void player_update(struct Player *self){
int speed = self->speed;
if (self->xPos >=600)
  self->speed = -3;
if (self->xPos <= 1)
  self->speed = 3;

  self->xPos += speed;
  if (self->yPos > 48)
    self->yPos -= 5;
  //self->yPos = 48;
}

void player_jump(struct Player *self){
  self->yPos += 96;

}
