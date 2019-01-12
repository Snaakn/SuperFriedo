// player struct
struct Player{
  int xPos;
  int yPos;
  void (*update)(struct Player *);
  //TODO add SDL_Image file so later it can be drawn via player.draw
};

void player_update(struct Player *);
