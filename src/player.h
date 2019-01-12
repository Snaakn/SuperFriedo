#include "gamewindow.h"

// player struct
struct Player{
  int xPos;
  int yPos;
  int speed;
  void (*update)(struct Player *);
  //TODO add SDL_Image file so later it can be drawn via player.draw
  SDL_Texture *texture;
};

void player_update(struct Player *);
