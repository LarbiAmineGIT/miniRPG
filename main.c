#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "perso.h" 


int main()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}
	SDL_Window *screen = SDL_CreateWindow("Mini_RPG",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

	SDL_Delay(4000);
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);

    SDL_SetRenderDrawColor(renderer , 0, 0, 0, 255);
    SDL_RenderClear(renderer );
    SDL_RenderPresent(renderer );

  
//PERSONNAGE -----------------------------------------------------------------------------------------------------------------------
    
    //attribus de l'image des Sprites
    const int SHEET_WIDTH = 1536;
    const int SHEET_HEIGHT = 2112;
    
    //Les surfaces
    SDL_Surface *perso = NULL;
    SDL_Surface *screen2 = NULL;
    
    //La structure d'événements
    SDL_Event event;
    
    //partie qui sera blitté
    SDL_Rect clip[1]; 


    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
    {

    //On coupe un sprite dans notre 
        clip[0].x = 0;
        clip[0].y = SHEET_HEIGHT/30.17;
        clip[0].w = SHEET_WIDTH/24;
        clip[0].h = SHEET_HEIGHT/30.17;


        SDL_Rect offset;
    
        offset.x = x;
        offset.y = y;
    
        //On blitte la surface
        SDL_BlitSurface( source, clip, destination, &offset );
    }

    //On applique les sprites sur l'écran
    apply_surface(0,0, perso, screen2, &clip[0]);
      
    
    
	SDL_Quit();
}
