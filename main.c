#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "enigme.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    TTF_Font *font = NULL;
    SDL_Color textColor = { 255, 255, 255 };
    enigme e;


    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
        exit(1);
    }


    if (TTF_Init() == -1)
    {
        fprintf(stderr, "TTF_Init() failed: %s\n", TTF_GetError());
        exit(1);
    }

    
    font = TTF_OpenFont("police.ttf", 40);
    if (font == NULL)
    {
        fprintf(stderr, "TTF_OpenFont() failed: %s\n", TTF_GetError());
        exit(1);
    }

    
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    if (screen == NULL)
    {
        fprintf(stderr, "SDL_SetVideoMode() failed: %s\n", SDL_GetError());
        exit(1);
    }

    
    initEnigme(&e, textColor);

    
    while (1)
    {
       
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                // Quit the game
                goto end;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    // Quit the game
                    goto end;
                }
            }
        }

        // Clear the screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        // Draw the enigma
        blit_enigme(&e, screen);

        // Update the screen
        SDL_Flip(screen);
    }

end:
    // Free resources
    free_surface_enigme(&e);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
