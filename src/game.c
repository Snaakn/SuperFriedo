#include "stdio.h"
#include "player.h"
#include "time.h"




//-------------------------------------------------------------------------



 int processEvent(SDL_Window *win, struct Player *self, GameState *game)
 {   self->yPos += self -> dPos;

    self->dPos -= 1;

   SDL_Event event;


   while(SDL_PollEvent(&event))
   {
     switch (event.type){
       case SDL_QUIT:
       game->done = 1;
       break;
     }

     // Get input

     const Uint8 *state = SDL_GetKeyboardState(NULL);
      if(state[SDL_SCANCODE_A]){
         self->xPos-= 10;
       }
        if(state[SDL_SCANCODE_D]){
           self->xPos+=10;
         }

             if(state[SDL_SCANCODE_SPACE]){
                  self->dPos += 30;


             }

           }

           return game->done;
         }



//---------------------------MAIN-------------------------------------------
int main(void)
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

//--------------- Philipps player struktur:----------------------
// the structure contains function pointers to update function or later walk and jump
// create an instance of type player: {xPos, yPos, update-function-to-point-to}
    struct Player player = {20, 144,0, 0, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/gumba.png"))};
    //SDL_FreeSurface(&player.texture);
    player.update(&player); // update changes player values
    printf("Player coords: %d,%d\n", player.xPos, player.yPos); //prints "Player coords: 2,3" not 0,0 since update changed the values
//---------------------------------------------------------------

struct Player boden = {60,120,0,20, player_update,player_jump, SDL_CreateTextureFromSurface(rend, IMG_Load("Images/boden.png"))};


   // bodenSurface = IMG_Load("Images/boden.png");
   // gameState.boden = SDL_CreateTextureFromSurface(rend, bodenSurface);
   // SDL_FreeSurface(bodenSurface);
   //gumbaSurface = IMG_Load("Images/gumba.png");
   //gameState.gumba = SDL_CreateTextureFromSurface(rend,gumbaSurface);
   //SDL_FreeSurface(gumbaSurface);


   int now, last;
   double deltatime;
   while(!game.done){
    last = SDL_GetPerformanceCounter();
    if(processEvent(win, &player, &game) == 1)
    game.done = 1;
    // TODO iterate over level array and choose textures from chars in array

    //collisionDetect(&gameState);

    player.update(&player); // update changes player values

// TODO create render function that iterates over level array and a list of active enemies to draw them
  SDL_SetRenderDrawColor(rend, 0,0,25,255);
    SDL_RenderClear(rend);
         doRender(rend, player.xPos,player.yPos, player.texture);
         doRender(rend, boden.xPos, boden.yPos, boden.texture);
    SDL_RenderPresent(rend);
//------------------------------------------------------------------------------

     now = SDL_GetPerformanceCounter();
     deltatime = (double)((now-last) / (double) SDL_GetPerformanceFrequency());
     SDL_Delay((1000-deltatime)/60);
   }
    //SDL_DestroyTexture(game.gumba);
    //SDL_DestroyTexture(game.boden);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
