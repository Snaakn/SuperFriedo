#include "gamewindow.h"
#include "camera.h"

// player struct
struct Player{
  int lives;
  int xPos;
  int yPos;
  int dY;
  int canjump;
  void (*update)(struct Player *, struct Cam *, char *, struct Level *);
  void (*jump)(struct Player *);

  //TODO add SDL_Image file so later it can be drawn via player.draw
  SDL_Texture *texture;
};




void player_update(struct Player *, struct Cam *, char *, struct Level *);
void player_jump(struct Player *);
