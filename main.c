#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL.h>
#include "perso.h"
//http://www.programmersranch.com/2014/03/sdl2-animations-with-sprite-sheets.html
const int SHEET_WIDTH = 1536;
const int SHEET_HEIGHT = 2112;

int main(int argc, char** argv)
{ 
    bool quit = false;
    SDL_Event event;
    
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
 
    SDL_Init(SDL_INIT_VIDEO);
    /* Création de la fenêtre */
    SDL_Window * window = SDL_CreateWindow("miniRPG",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 512, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * fond = SDL_LoadBMP("../fond.bmp");
    SDL_Surface * image = SDL_LoadBMP("nEFACHdg.bmp");
    SDL_Texture * background = SDL_CreateTextureFromSurface(renderer, fond);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    
	personnage* perso = init_personnage( (SDL_GetTicks()/100)%9, 71*10, SHEET_WIDTH/24, 71);
    int x = 0; 
    int y = 0;
    
    
    while (!quit)
    {   
        //gives us the number of milliseconds that passed since the program started so you can know which sprite to use. Divide by 1000 to get the time in seconds 
        Uint32 ticks = SDL_GetTicks();
        Uint32 seconds = ticks / 100;
        // We divide by 7 because we have 7 sprites fr our first animation
        Uint32 sprite = seconds % 9;
        
        //source region
        //SDL_Rect srcrect = { sprite * SHEET_WIDTH/24,71*10 ,SHEET_WIDTH/24,71 };
        //destination region
        //SDL_Rect dstrect = { x + 100, y + 100, SHEET_WIDTH/24, 71};
        
        while(SDL_PollEvent(&event) != NULL)
        {
            switch (event.type)
            {
                
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:  left_move(perso, 71*10); break;
                        case SDLK_RIGHT: right_move(perso, 71*10); break;
                        case SDLK_UP:    down_move(perso, 71*10); break;
                        case SDLK_DOWN:  up_move(perso, 71*10); break;
                    }
                    break;
            }
	    SDL_Delay(10);
        }
        SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, texture, &perso->srcrect, &perso->dstrect);
        SDL_RenderPresent(renderer);
    }
    
    /* Attendre trois secondes, que l'utilisateur voie la fenêtre + Cas de l'erreur de la création de la fenêtre */
    /*if( window )
        {
            SDL_Delay(3000);  
            SDL_DestroyWindow(window);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }*/
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
 
    return 0;

}
