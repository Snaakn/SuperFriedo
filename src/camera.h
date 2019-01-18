struct Cam {
  int xPos;
  int yPos;
  int arrX;
  int arrY;
  int automove;
  void (*update)(struct Cam *);
};

void cam_update(struct Cam *);
