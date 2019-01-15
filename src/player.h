#include "gamewindow.h"

// player struct
struct Player{
  float xPos;
  float yPos;
 float dY;
  float dX;

  void (*update)(struct Player *);
  void (*jump)(struct Player *);

  //TODO add SDL_Image file so later it can be drawn via player.draw
  SDL_Texture *texture;
};

void player_update(struct Player *);
void player_jump(struct Player *);
