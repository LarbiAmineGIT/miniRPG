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
    SDL_Surface * fond = SDL_LoadBMP("../fond.bmp");
    SDL_Surface * image = SDL_LoadBMP("nEFACHdg.bmp");
    SDL_Surface * monster = SDL_LoadBMP("ZlTqEth+.bmp");
    
    //Create texture
    SDL_Texture * background = SDL_CreateTextureFromSurface(renderer, fond);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Texture * creature = SDL_CreateTextureFromSurface(renderer, monster);
   
   //Initialisation of character and monsters' array
    personnage* perso = init_personnage( (SDL_GetTicks()/100)%9, 71*10, SHEET_WIDTH/24, 71);
    monstre** monster_array = init_tab_monstre();
    int nb_monstre = 0;
    

    //Game's loop
    while (!quit)
    {   
        //gives us the number of milliseconds that passed since the program started so you can know which sprite to use. Divide by 1000 to get the time in seconds 
        Uint32 ticks = SDL_GetTicks();
        Uint32 seconds = ticks / 100;
        // We divide by 7 because we have 7 sprites fr our first animation
        Uint32 sprite = seconds % 9;
        
        while(SDL_PollEvent(&event) != NULL)
        {
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
					left_move(perso, 72.75*8);
				}
				break;
                        case SDLK_RIGHT:
				if(perso->x < 1024 - SHEET_WIDTH/24) {
					right_move(perso, 71*10);
				}
				break;
                        case SDLK_UP:
				if(perso->y > 3) {
					down_move(perso, 74*7);
				}
				break;
                        case SDLK_DOWN:
				if(perso->y < 512 - 71) {
					up_move(perso, 71*9);
				}
				break;
                    }
                    break;
            }
	    if(my_rand() < 512 && nb_monstre < 10) {
		    monster_array[nb_monstre] = init_monstre(sprite, 71*10, SHEET_WIDTH/24, 71);
		    nb_monstre++;
	    }
	    SDL_RenderClear(renderer);
	    SDL_RenderCopy(renderer, background, NULL, NULL);
	    SDL_RenderCopy(renderer, texture, &perso->srcrect, &perso->dstrect);
	    for(int i=0 ; i<nb_monstre ; i++) {
		    SDL_RenderCopy(renderer, creature, &monster_array[i]->srcrect, &monster_array[i]->dstrect);
	    }
	    SDL_RenderPresent(renderer);

	    SDL_Delay(10);
        }
    }
    
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(creature);

    SDL_FreeSurface(image);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(monster);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
 
    return 0;

}
