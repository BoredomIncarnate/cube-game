#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* global_Window = NULL;
SDL_Surface* global_screenSurface = NULL;
SDL_Surface* global_Background = NULL;

bool init() 
{
  bool success = true;

  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not init %s\n", SDL_GetError() );
  }
  else 
  {
    global_Window = SDL_CreateWindow( 
      "CUBE GAME", 
      SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, 
      SCREEN_WIDTH, 
      SCREEN_HEIGHT, 
      SDL_WINDOW_SHOWN 
    );

    if ( global_Window == NULL ) 
    {
      // something went wrong
      printf( "AH SHIT! Something done fugged when trying to get the gosh darn global winder. Error details: %s\n", SDL_GetError() );

      // TODO: in the future use constants to assign specific error values
      success = false; // set success to a failure
    }
    else
    {
      global_screenSurface = SDL_GetWindowSurface( global_Window );
    } 
  }
  
  return success;
}

bool loadMedia() 
{
  bool success = true;
  const char *image_path = "images/smokey_purp_bg.bmp";
  global_Background = SDL_LoadBMP( image_path );

  if ( global_Background == NULL )
  {
    printf( "AH SHIT! Something done fugged when trying to get the gosh darn background. Error details: %s\n", SDL_GetError() );
    success = false;
  }

  return success;
}

void close_sdl() 
{
  SDL_FreeSurface( global_Background );
  SDL_DestroyWindow( global_Window );
  global_Window = NULL;
  SDL_Quit();
}

int main(int argc, char* argv[]) {
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;

  if ( init() == false )
  {
    printf( "SDL could not init %s\n", SDL_GetError() );
  }
  else 
  {
    if ( loadMedia() == false)
    {
      printf( "SDL could not load media %s\n", SDL_GetError() );
    }
    else 
    {
      SDL_Event e; 
      int quit = 0; 
      while( quit == 0 )
      { 
        while( SDL_PollEvent( &e ) )
        { 
          if( e.type == SDL_QUIT ) {
            quit = 1;
          }  
        } 

        SDL_BlitSurface( global_Background, NULL, global_screenSurface, NULL );
        SDL_UpdateWindowSurface( global_Window );
      }
    }
  }

  close_sdl();
  return 0;
}
