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
