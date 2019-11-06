#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL.h>


int main(int argc, char** argv)
{
    bool quit = false;
    
   /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* window = NULL;
        window = SDL_CreateWindow("minirpg",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
        
        SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Surface * image = SDL_LoadBMP("tux-sit.bmp");
        SDL_Texture* monImage = SDL_CreateTextureFromSurface(renderer,image);
        
        while (!quit){
    
            SDL_RenderCopy(renderer, monImage, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
 
        SDL_DestroyTexture(monImage);
        SDL_FreeSurface(image);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        
        
        if( window )
        {
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_DestroyWindow(window);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }
    
 /* 
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
*/      
    SDL_Quit();

    return 0;
    
   
}
