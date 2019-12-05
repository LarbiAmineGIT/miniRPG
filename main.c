#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL.h>
#include "perso.h"
#include "monstre.h"

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
    
    //Load BMP image
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * grass_background = SDL_LoadBMP("../grass.bmp");
    SDL_Surface * character_sprite = SDL_LoadBMP("../character.bmp");
    SDL_Surface * skeleton_sprite = SDL_LoadBMP("../skeleton.bmp");
    
    //Create texture
    SDL_Texture * grass = SDL_CreateTextureFromSurface(renderer, grass_background);
    SDL_Texture * character = SDL_CreateTextureFromSurface(renderer, character_sprite);
    SDL_Texture * skeleton = SDL_CreateTextureFromSurface(renderer, skeleton_sprite);
   
   //Initialisation of character and monsters' array
    personnage* perso = init_personnage( (SDL_GetTicks()/100)%9, 71*10, SHEET_WIDTH/24, 71);
    monstre** monster_array = init_tab_monstre();
    int nb_monstre = 0;


    //Game's loop
    while (!quit)
    {   
        
        while(SDL_PollEvent(&event) != NULL)
        {
		Uint32 image = SDL_GetTicks() / 100;
            switch (event.type)
            {
                SDL_PollEvent(&event);
                
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
				if(perso->x > 3) {
					left_move(perso, 72.75*8, SDL_GetTicks()/100%9);
				}
				break;
                        case SDLK_RIGHT:
				if(perso->x < 1024 - SHEET_WIDTH/24) {
					right_move(perso, 71*10, image%9);
				}
				break;
                        case SDLK_UP:
				if(perso->y > 3) {
					down_move(perso, 74*7, image%9);
				}
				break;
                        case SDLK_DOWN:
				if(perso->y < 512 - 71) {
					up_move(perso, 71*9, image%9);
				}
				break;
                    }
                    break;
            }
	    if(my_rand() < 512 && nb_monstre < 10) {
		    monster_array[nb_monstre] = init_monstre(image%9, 71*10, SHEET_WIDTH/24, 71);
		    nb_monstre++;
	    }
	    SDL_RenderClear(renderer);
	    SDL_RenderCopy(renderer, background, NULL, NULL);
	    SDL_RenderCopy(renderer, character, &perso->srcrect, &perso->dstrect);
	    for(int i=0 ; i<nb_monstre ; i++) {
		    SDL_RenderCopy(renderer, skeleton, &monster_array[i]->srcrect, &monster_array[i]->dstrect);
	    }
	    SDL_RenderPresent(renderer);
	    SDL_Delay(10);
        }
    }
    
    SDL_DestroyTexture(character);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(skeleton);

    SDL_FreeSurface(character_sprite);
    SDL_FreeSurface(grass_background);
    SDL_FreeSurface(skeleton_sprite);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
 
    return 0;

}
