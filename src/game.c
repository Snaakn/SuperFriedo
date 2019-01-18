#include "level.h"
#include "player.h"

//#include "time.h"


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

  void getInput(GameState *game, struct Player *p, struct Cam *c){

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // Quit game by pressing esc
    if(state[SDL_SCANCODE_ESCAPE])
      game->done = 1;

    // Player Jump
    if(state[SDL_SCANCODE_SPACE]){
      p->jump(p);
    }
    if(!state[SDL_SCANCODE_SPACE]){
      p->canjump = 1;
    }
    // Player move left
    if(state[SDL_SCANCODE_A]){
      p->xPos -= 4;
    }
    // Player move right
    if(state[SDL_SCANCODE_D]){
      if (p->xPos >=c->xPos+SCREEN_WIDTH/2){

        c->xPos += 4;
      }
      p->xPos += 4;
    }
  }

//-------------------------------------------------------------------------

  // Collision will not be possible until camera is working
  // we NEED camera coords otherwise we can do it all again later!

 // int collision(int p_xPos, int p_yPos, int p_xSpeed, int p_ySpeed){
 //   // to array coords:
 //   //Something like this
 //    (camera_xPos-(p_xPos+p_xSpeed))/48
 //   if (lvl_arr[y*SCREEN_HEIGHT+x] == #)
 //     return 1; // 1 is for Block
 //
 //   // enemy collision will work different
 //
 //   //return no collision
 //   return 0;
 // }


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
// create an instance of type player: {xPos, yPos, update-function-to-point-to}
  struct Player player = {300, 144,0,1, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/gumba.png"))};
// possible player 2
// struct Player fred = {300, 144, -3, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/gumba.png"))};
//----------------------------------------------------------------

// create level arrays and load level file
  static Level lvl;
  prepare_level(&lvl);
  char *lvl_arr = malloc((lvl.width*lvl.height)*sizeof(char));
  load_level(lvl_arr,&lvl);

// TODO make an Enemy struct
// list of enemies
// struct Enemy *enems = malloc(lvl.enem_count*sizeof(struct Enemy));

// TODO make a Block struct I will use player struct for now
  struct Player boden = {96,96,0,0, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/boden.png"))};
  struct Cam camera = {0,(lvl.height-1)*48,0,lvl.height,0, cam_update};
/***********************************************************************/
   int now, last;
   double deltatime;
   //printf("%d, %d\n", lvl.height,lvl.width);

   while(!game.done){
    last = SDL_GetPerformanceCounter();
    getInput(&game, &player, &camera);
    if(processEvent(win, &game) == 1)
    game.done = 1;
//-----------------------------------UPDATE CALL--------------------------------
    camera.update(&camera);
    player.update(&player, &camera); // update changes player values

// TODO create render function that iterates over level array and a list of active enemies to draw them
  SDL_SetRenderDrawColor(rend, 0,0,25,255);
    SDL_RenderClear(rend);
      //doRender(rend, fred.xPos, fred.yPos, fred.texture);

      // for (int i = lvl.height-1; i >= 0  ; i--) {
      //   for (int j = 0; j < lvl.width; j++) {
      for (int i = camera.arrY; i >= 0  ; i--) {
        for (int j = camera.arrX; j < camera.arrX+15; j++) {
          //printf("%c", lvl_arr[(i*lvl.width)+j]);

          if (lvl_arr[(i*lvl.width)+j] == '#'){
            doRender(rend, j*48-camera.xPos, ((lvl.height-i)*48), boden.texture);
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
