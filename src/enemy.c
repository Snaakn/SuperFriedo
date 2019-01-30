#include "enemy.h"

void enemy_update(struct Enemy *self,char *lvl_arr, struct Level *level){
  if (x_collision(self->xPos, self->yPos,self->speed, lvl_arr, level))
    self->speed *= -1;

  self->xPos += self->speed*GAMESPEED;

}
