#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

struct Personnage {
	double x;
	double y;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};
typedef struct Personnage personnage;

personnage* init_personnage(int time, int placex, int width, int height);

void right_move(personnage* perso, int placex, int placey);

void left_move(personnage* perso, int placex, int placey);

void up_move(personnage* perso, int placex, int placey);

void down_move(personnage* perso, int placex, int placey);
#endif
