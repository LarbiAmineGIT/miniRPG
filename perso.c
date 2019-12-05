#include "perso.h"

personnage* init_personnage(int time, int placey, int width, int height) {
	personnage* perso = malloc(sizeof(personnage));

	perso->x = 100;
	perso->y = 100;

	perso->srcrect.x = time;
	perso->srcrect.y = placey;
	perso->srcrect.w = width;
	perso->srcrect.h = height;

	perso->dstrect.x = perso->x;
	perso->dstrect.y = perso->y;
	perso->dstrect.w = width;
	perso->dstrect.h = height;

	return perso;
}

void right_move(personnage* perso, int placey, int placex) {
	perso->x = perso->x + 8;
	perso->dstrect.x = perso->x;
	perso->srcrect.y = placey;
}

void left_move(personnage* perso, int placey, int placex) {
	perso->x = perso->x - 8;
	perso->dstrect.x = perso->x;
	perso->srcrect.y = placey;
}

void up_move(personnage* perso, int placey, int placex) {
	perso->y = perso->y + 8;
	perso->dstrect.y = perso->y;
	perso->srcrect.y = placey;
}

void down_move(personnage* perso, int placey, int placex) {
	perso->y = perso->y - 8;
	perso->dstrect.y = perso -> y;
	perso->srcrect.y = placey;
}
