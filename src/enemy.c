#include <enemy.h>

void enemy_update (struct Enemy *self,char *lvl_arr,struct Level *level){

  if (xcollision(self->xPos, self->yPos,self->speed, self->dY, lvl_arr, level))





}
