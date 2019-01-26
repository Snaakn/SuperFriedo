struct Coin{
  int xPos;
  int yPos;
  int isCollected;
  void (*update)(struct Coin *);
};

void coin_update(struct Coin *);
