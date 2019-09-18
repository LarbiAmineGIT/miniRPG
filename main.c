#import <stdlib.h>
#import <stdio.h>
#import <stdbool.h>
#include "SDL.h"

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Quit();
}
