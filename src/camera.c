#include "camera.h"

void cam_update(struct Cam *self){
  self->arrX = (int) (self->xPos/48);
  self->arrY = (int) (self->yPos/48);
}
