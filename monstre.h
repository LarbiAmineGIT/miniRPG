#ifndef MONSTRE_H
#define MONSTRE_H

#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

struct Monster {
	double x;
	double y;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};
typedef struct Monster monstre;

int my_rand();

monstre** init_tab_monstre();

monstre* init_monstre(int time, int place, int width, int height);

#endif
