#include "perso.h"

personnage* init_personnage(int time, int placex, int width, int height) {
	personnage* perso = malloc(sizeof(personnage));

	perso->x = 100;
	perso->y = 100;

	perso->srcrect.x = time;
	perso->srcrect.y = placex;
	perso->srcrect.w = width;
	perso->srcrect.h = height;

	perso->dstrect.x = perso->x;
	perso->dstrect.y = perso->y;
	perso->dstrect.w = width;
	perso->dstrect.h = height;

	return perso;
}

void right_move(personnage* perso, int placex, int placey) {
	perso->x = perso->x + 8;
	perso->dstrect.x = perso->x;
	perso->srcrect.y = placex;
	perso->srcrect.x = placey;
}

void left_move(personnage* perso, int placex, Uint32 placey) {
	perso->x = perso->x - 8;
	perso->dstrect.x = perso->x;
	perso->srcrect.y = placex;
	perso->srcrect.x = placey;
}

void up_move(personnage* perso, int placex, int placey) {
	perso->y = perso->y + 8;
	perso->dstrect.y = perso->y;
	perso->srcrect.y = placex;
}

void down_move(personnage* perso, int placex, int placey) {
	perso->y = perso->y - 8;
	perso->dstrect.y = perso -> y;
	perso->srcrect.y = placex;
}
