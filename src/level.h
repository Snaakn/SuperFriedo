#include "stdio.h"
#include "stdlib.h"

typedef struct {
  int width;
  int height;
  int enem_count;
}Level;

void prepare_level(Level *);
void load_level(char *,Level *level);
