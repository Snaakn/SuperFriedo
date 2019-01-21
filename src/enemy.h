#include "player.h"

struct Enemy{
  int isAlive;
  int isSpawned;
  int speed;
  int xPos;
  int yPos;
  int dY;
  void (*update)(struct Enemy *, char *, struct Level *);
  SDL_Texture *texture;
};

void enemy_update (struct Enemy *, char *, struct Level *);
