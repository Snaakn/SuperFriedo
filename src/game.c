#include "enemy.h"

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

  void getInput(GameState *game, struct Player *p, struct Cam *c, char *l_a, struct Level *l, struct Background *b1, struct Background *b2){

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
          b1->xPos -= 3;
          b2->xPos -= 3;
        }
        p->xPos += 4;
      }
    }
  }

//-------------------------------------------------------------------------

int x_collision(int x, int y, int x_dir, char *lvl_arr, struct Level *l){
  int next_X = (int)((x+x_dir+4)/TILE_SIZE);
  int next_X2 = (int)((x+x_dir+40)/TILE_SIZE);
  int next_Y = ((l->height-1)-(int)((y-TILE_SIZE)/TILE_SIZE));

  if ((lvl_arr[next_Y*(l->width)+next_X] == '#') || (lvl_arr[next_Y*(l->width)+next_X2] == '#')) {
    return 1;
  }


  return 0;
}

int collision(int x, int y, int x_dir, int y_dir, char *lvl_arr, struct Level *l){
  int next_X = (int)((x+x_dir+4)/TILE_SIZE);
  int next_X2 = (int)((x+x_dir+40)/TILE_SIZE);
  int next_Y = ((l->height-1)-(int)((y+y_dir-TILE_SIZE)/TILE_SIZE));
  int next_Y2 = ((l->height-1)-(int)((y+y_dir-(TILE_SIZE/4))/TILE_SIZE));

  //printf("%d, %d\n", next_X, next_Y);
  //printf("%c",lvl_arr[next_Y*(l->width)+next_X]);
  if ((lvl_arr[next_Y*(l->width)+next_X] == '#') || (lvl_arr[next_Y*(l->width)+next_X2] == '#') || (lvl_arr[next_Y2*(l->width)+next_X] == '#') || (lvl_arr[next_Y2*(l->width)+next_X2] == '#')){
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



  SDL_Window* win = SDL_CreateWindow(SCREEN_NAME,
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE);

// create a renderer, which sets up the graphics hardware
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

  SDL_Surface *s_gumba = IMG_Load("Images/gumba.png");
  SDL_Surface *s_block = IMG_Load("Images/block.png");
  SDL_Surface *s_coin = IMG_Load("Images/coin.png");
  SDL_Surface *s_player = IMG_Load("Images/gumba.png");
  SDL_Surface *s_backgroud = IMG_Load("Images/background.png");

  // create Textures from surfaces
  SDL_Texture *gumba_texture = SDL_CreateTextureFromSurface(rend, s_gumba);
  SDL_Texture *block_texture = SDL_CreateTextureFromSurface(rend, s_block);
  SDL_Texture *coin_texture = SDL_CreateTextureFromSurface(rend, s_coin);
  SDL_Texture *player_texture = SDL_CreateTextureFromSurface(rend, s_player);
  SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(rend, s_backgroud);

//---UI-------------------------------
//------------------------------------

struct Background bg1 = {0, background_update};
struct Background bg2 = {SCREEN_WIDTH*2, background_update};

// create level arrays and load level file
static struct Level lvl;
prepare_level(&lvl);
char *lvl_arr = malloc((lvl.width*lvl.height)*sizeof(char));
load_level(lvl_arr,&lvl);

/************************CREATE ENTITIES*******************************/
//--------------- Philipps player struktur:----------------------
// the structure contains function pointers to update function or later walk and jump
struct Player player = {/*score*/0,/*lives*/3,/*xpos*/300, /*ypos*/144,/*dY*/0,/*canjump*/1, player_update,player_jump, player_texture};
// create an instance of type player: {lives, xPos, yPos, update-function-to-point-to}

//-----------------Create enemies--------------------------------
struct Enemy *gumba = calloc(lvl.enem_count, sizeof(struct Enemy));
int gcount = 0;
struct Enemy prototype = {1,0,-2,0,0,0, enemy_update, gumba_texture};
for (int i = 0; i < lvl.enem_count; i++) {
  gumba[i] = prototype;
}

// TODO make a Block struct I will use player struct for now
struct Player boden = {0,0,96,96,0,0, player_update,player_jump, block_texture};
struct Cam camera = {0,(lvl.height-1)*TILE_SIZE,0,lvl.height,0, cam_update};
/***********************************************************************/
int now, last;
double deltatime;
//printf("%d, %d\n", lvl.height,lvl.width);

// Gameloop---------------------------------------------------------------------
while(!game.done){
  last = SDL_GetPerformanceCounter();
  getInput(&game, &player, &camera, lvl_arr, &lvl, &bg1, &bg2);
  if(processEvent(win, &game) == 1)
  game.done = 1;
  //----------------------UPDATE CALLS--------------------------------
  camera.update(&camera);
  player.update(&player, &camera, lvl_arr, &lvl); // update changes player values
  //update enemies
  for (int i = 0; i < lvl.enem_count; i++) {
    if(gumba[i].isSpawned && gumba[i].isAlive){
      gumba[i].update(&gumba[i], lvl_arr, &lvl);
    }
  }
  bg1.update(&bg1);
  bg2.update(&bg2);
  //----------------------------------------------------------------------------

  // clear screen
  SDL_RenderClear(rend);
  doRender(rend, bg1.xPos, SCREEN_HEIGHT, SCREEN_WIDTH*2, SCREEN_HEIGHT, bg_texture);
  doRender(rend, bg2.xPos, SCREEN_HEIGHT, SCREEN_WIDTH*2, SCREEN_HEIGHT, bg_texture);
  // show players lives
  for(int i = 0; i< player.lives;i++){
    doRender(rend, (i)*TILE_SIZE,SCREEN_HEIGHT, TILE_SIZE, TILE_SIZE, player.texture);
  }
  for (int i = camera.arrY; i >= 0  ; i--) {
    for (int j = camera.arrX; j < camera.arrX+((SCREEN_WIDTH+(2*TILE_SIZE))/(TILE_SIZE)); j++) {
      if (lvl_arr[(i*lvl.width)+j] == '#'){
        doRender(rend, j*TILE_SIZE-camera.xPos, ((lvl.height-i)*TILE_SIZE), TILE_SIZE, TILE_SIZE, boden.texture);
      }
      if (lvl_arr[(i*lvl.width)+j] == 'G' && !gumba[gcount].isSpawned){
        gumba[gcount].isSpawned = 1;
        gumba[gcount].xPos = j*TILE_SIZE-camera.xPos;
        gumba[gcount].yPos = (lvl.height-i)*TILE_SIZE;
        if(gcount != lvl.enem_count)
          gcount ++;
      }
      if (lvl_arr[(i*lvl.width)+j] == 'C'){
        doRender(rend, j*TILE_SIZE-camera.xPos, ((lvl.height-i)*TILE_SIZE), TILE_SIZE, TILE_SIZE, coin_texture);
      }

    }
  }
  // draw Player
  doRender(rend, player.xPos-camera.xPos,player.yPos, TILE_SIZE, TILE_SIZE, player.texture);
  // draw enemies
  for (int i = 0; i < lvl.enem_count; i++) {
    if(gumba[i].isSpawned && gumba[i].isAlive)
      doRender(rend, gumba[i].xPos-camera.xPos, gumba[i].yPos, TILE_SIZE, TILE_SIZE, gumba[i].texture);
  }

  SDL_RenderPresent(rend);

  // calculate deltatime to compensate lag
  now = SDL_GetPerformanceCounter();
  deltatime = (double)((now-last) / (double) SDL_GetPerformanceFrequency());
  SDL_Delay((1000-deltatime)/60);
} //----------------------------------------------------------------------------

    SDL_DestroyTexture(player_texture);
    SDL_DestroyTexture(gumba_texture);
    SDL_DestroyTexture(block_texture);
    SDL_DestroyTexture(coin_texture);

    SDL_FreeSurface(s_player);
    SDL_FreeSurface(s_gumba);
    SDL_FreeSurface(s_block);
    SDL_FreeSurface(s_coin);

    free(lvl_arr);
    free(gumba);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
