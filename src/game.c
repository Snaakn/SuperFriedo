//#include "level.h"
#include "player.h"

//#include "time.h"

int spacenotpressed = 1;

int processEvent(SDL_Window *win, GameState *game) {

  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type){
      case SDL_QUIT:
        game->done = 1;
        break;
    }



  }
  return game->done;
}

  void getInput(GameState *game, struct Player *p, struct Cam *c, char *l_a, struct Level *l){

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // Quit game by pressing esc
    if(state[SDL_SCANCODE_ESCAPE])
      game->done = 1;
    if (p->lives < 0){
      printf("Game Over\n");
      game->done = 1;
    }
    // Player Jump
    if(state[SDL_SCANCODE_SPACE] && spacenotpressed){
      p->jump(p);
      spacenotpressed = 0;
    }
    if(!state[SDL_SCANCODE_SPACE]){
      spacenotpressed = 1;
    }
    // Player move left
    if(state[SDL_SCANCODE_A]){
      if (!x_collision(p->xPos, p->yPos, -4, l_a, l))
        p->xPos -= 4;
    }
    // Player move right
    if(state[SDL_SCANCODE_D]){
      if (!x_collision(p->xPos, p->yPos, 4, l_a, l)){
        if (p->xPos >=c->xPos+SCREEN_WIDTH/2){
          c->xPos += 4;
        }
        p->xPos += 4;
      }
    }
  }

//-------------------------------------------------------------------------

int x_collision(int x, int y, int x_dir, char *lvl_arr, struct Level *l){
  int next_X = (int)((x+x_dir+8)/TILE_SIZE);
  int next_X2 = (int)((x+x_dir+38)/TILE_SIZE);
  int next_Y = ((l->height-1)-(int)((y-TILE_SIZE)/TILE_SIZE));

  if ((lvl_arr[next_Y*(l->width)+next_X] == '#') || (lvl_arr[next_Y*(l->width)+next_X2] == '#')) {
    return 1;
  }


  return 0;
}

int collision(int x, int y, int x_dir, int y_dir, char *lvl_arr, struct Level *l){
  int next_X = (int)((x+x_dir+8)/TILE_SIZE);
  int next_X2 = (int)((x+x_dir+38)/TILE_SIZE);
  int next_Y = ((l->height-1)-(int)((y+y_dir-TILE_SIZE)/TILE_SIZE));
  int next_Y2 = ((l->height-1)-(int)((y+y_dir-TILE_SIZE)/TILE_SIZE));

  printf("%d, %d\n", next_X, next_Y);
  //printf("%c",lvl_arr[next_Y*(l->width)+next_X]);
  if ((lvl_arr[next_Y*(l->width)+next_X] == '#') || (lvl_arr[next_Y*(l->width)+next_X2] == '#') || (lvl_arr[next_Y*(l->width)+next_X] == '#') || (lvl_arr[next_Y*(l->width)+next_X2] == '#')){
    //printf("collision\n");
    return 1;
  }
  return 0;
}


//---------------------------MAIN-------------------------------------------
int main(int argc, char *argv[])
{
  GameState game;
  game.done = 0;
  SDL_Surface *bodenSurface = NULL;
  SDL_Surface *gumbaSurface = NULL;

  SDL_Window* win = SDL_CreateWindow(SCREEN_NAME,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE);

// create a renderer, which sets up the graphics hardware
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
/************************CREATE ENTITIES*******************************/
//--------------- Philipps player struktur:----------------------
// the structure contains function pointers to update function or later walk and jump
// create an instance of type player: {lives, xPos, yPos, update-function-to-point-to}
  struct Player player = {3,300, 144,0,1, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/gumba.png"))};
// possible player 2
// struct Player fred = {300, 144, -3, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/gumba.png"))};
//----------------------------------------------------------------

//---UI-------------------------------
SDL_Texture *lives_image = SDL_CreateTextureFromSurface(rend, IMG_Load("Images/lives.png"));
//------------------------------------

// create level arrays and load level file
  static struct Level lvl;
  prepare_level(&lvl);
  char *lvl_arr = malloc((lvl.width*lvl.height)*sizeof(char));
  load_level(lvl_arr,&lvl);

// TODO make an Enemy struct
// list of enemies
// struct Enemy *enems = malloc(lvl.enem_count*sizeof(struct Enemy));

// TODO make a Block struct I will use player struct for now
  struct Player boden = {0,96,96,0,0, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/boden.png"))};
  struct Cam camera = {0,(lvl.height-1)*TILE_SIZE,0,lvl.height,0, cam_update};
/***********************************************************************/
   int now, last;
   double deltatime;
   //printf("%d, %d\n", lvl.height,lvl.width);

   while(!game.done){
    last = SDL_GetPerformanceCounter();
    getInput(&game, &player, &camera, lvl_arr, &lvl);
    if(processEvent(win, &game) == 1)
    game.done = 1;
//-----------------------------------UPDATE CALL--------------------------------
    camera.update(&camera);
    player.update(&player, &camera, lvl_arr, &lvl); // update changes player values
//----------------------------------------------------------------------------

// TODO create render function that iterates over level array and a list of active enemies to draw them
  SDL_SetRenderDrawColor(rend, 0,0,25,255);
    SDL_RenderClear(rend);
      //doRender(rend, fred.xPos, fred.yPos, fred.texture);

    for(int i = 0; i< player.lives;i++){
      doRender(rend, (i)*TILE_SIZE,SCREEN_HEIGHT, player.texture);
    }


      for (int i = camera.arrY; i >= 0  ; i--) {
        for (int j = camera.arrX; j < camera.arrX+((SCREEN_WIDTH+(2*TILE_SIZE))/(TILE_SIZE)); j++) {
          //printf("%c", lvl_arr[(i*lvl.width)+j]);

          if (lvl_arr[(i*lvl.width)+j] == '#'){
            doRender(rend, j*TILE_SIZE-camera.xPos, ((lvl.height-i)*TILE_SIZE), boden.texture);
          }
        }
      }

      doRender(rend, player.xPos-camera.xPos,player.yPos, player.texture);
    SDL_RenderPresent(rend);
//------------------------------------------------------------------------------

     now = SDL_GetPerformanceCounter();
     deltatime = (double)((now-last) / (double) SDL_GetPerformanceFrequency());
     SDL_Delay((1000-deltatime)/60);
   }
    //SDL_DestroyTexture(game.gumba);
    //SDL_DestroyTexture(game.boden);
    free(lvl_arr);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
