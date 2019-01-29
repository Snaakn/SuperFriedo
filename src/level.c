#pragma once
#include "stdio.h"
#include "level.h"

void prepare_level(struct Level *level){
  FILE *file;
  file = fopen("levels/level1.txt", "r");

  //count lines and characters in file
  char sgch; // holds single char
  int chars=0; // holds number of chars in one line
  int longest = 0; // finds the number of chars of the longest line
  int lines = 0; // holds the number of lines
  int enems = 0;
  int coins = 0;
  printf("reading file\n");
  while ((sgch = fgetc(file)) != EOF){
    chars++;
    //printf("%d\n", sgch);
    if (sgch == '\n'){
      lines++;
      if (chars > longest){
        longest = chars;
      }
      chars = 0;
    }
    if (sgch == 'G')
    	enems++;
 	if (sgch == 'C')
		coins++;


  }
  // now that we have the dimensions of the level
  // we can dynamically allocate an array to hold it
  level->enem_count = enems;
  level->width = longest;
  level->height = lines;
  level->coin_count = coins;
  fclose(file);
  //printf("level prepared\n");
  }


void load_level(char *arr, struct Level *level){
  FILE *file;
  file = fopen("levels/level1.txt", "r");
  int c=0;
  for (int i = 0; i < level->height; i++) {
    for (int j = 0; j < level->width; j++) {
      //c = fgetc(file);
        arr[(i*(level->width))+j] = (char) fgetc(file);
    }
  }
}
