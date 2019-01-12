#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>



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
  Gumba a;
  Block block[100];
  SDL_Texture *boden;
  SDL_Texture *gumba;

}GameState;
