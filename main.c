#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}
	SDL_Window *screen = SDL_CreateWindow("Mini_RPG",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

	SDL_Delay(4000);

	SDL_Quit();
}
