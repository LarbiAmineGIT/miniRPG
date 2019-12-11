#ifndef MONSTRE_H
#define MONSTRE_H

#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

struct Monster {
	double x;
	double y;
	char* name;
	int pv;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};
typedef struct Monster monstre;

int my_rand();

monstre** init_tab_monstre();

monstre* init_monstre(char* nom, int time, int place, int width, int height);

#endif
