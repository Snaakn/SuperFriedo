#include "level.h"

typedef struct
{
  int x,y;
  short life;
  float dy;
  char *name;

} Gumba;
typedef struct{
  int x,y,w,h;
}Block;

typedef struct
{
  int done;
  Block block[100];
  // SDL_Texture *boden;
  // SDL_Texture *gumba;

}GameState;

int collision(int x, int y, int x_dir, int y_dir, char *lvl_arr, struct Level *l);
int x_collision(int x, int y, int x_dir, char *lvl_arr, struct Level *l);
