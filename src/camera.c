#pragma once
#include "camera.h"
#include "gamewindow.h"

void cam_update(struct Cam *self){
  self->arrX = (int) (self->xPos/TILE_SIZE);
  self->arrY = (int) (self->yPos/TILE_SIZE);
}
