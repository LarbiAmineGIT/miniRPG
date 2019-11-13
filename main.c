#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL.h>

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
    SDL_Window * window = SDL_CreateWindow("miniRPG",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = SDL_LoadBMP("nEFACHdg.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    
    //destination region
    SDL_Rect dstrect = { 10, 10, 64, 48 };
    SDL_Rect srcrect = { 0, 0, SHEET_WIDTH/24, SHEET_HEIGHT/30.17 };
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
        
        SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        SDL_RenderPresent(renderer);
    }
    
    /* Attendre trois secondes, que l'utilisateur voie la fenêtre + Cas de l'erreur de la création de la fenêtre */
    if( window )
        {
            SDL_Delay(3000);  
            SDL_DestroyWindow(window);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
 
    return 0;

}
