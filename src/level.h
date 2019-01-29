struct Level{
  int width;
  int height;
  int enem_count;
  int coin_count;
};

void prepare_level(struct Level *);
void load_level(char *,struct Level *level);
