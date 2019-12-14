#include "monstre.h"

int my_rand() {
	srand(time(NULL));
	return rand() % 1024;
}

int pv_rand() {
	srand(time(NULL));
	return rand() % 10 + 11;
}

monstre** init_tab_monstre() {
	monstre** tab = malloc(sizeof(monstre*)*10);
	return tab;
}

monstre* init_monstre(char* nom, int time, int place, int width, int height) {
	monstre* mob = malloc(sizeof(monstre));

	mob->x = my_rand()*2;
	if(mob->x > 1024) {
		mob->x = 1024 - 70;
	}
	mob->y = my_rand();
	if(mob->y > 512) {
		mob->y = 512 - 70;
	}
	mob->name = nom;
	mob->pv = pv_rand();

	mob->srcrect.x = time;
	mob->srcrect.y = place;
	mob->srcrect.w = width;
	mob->srcrect.h = height;

	mob->dstrect.x = mob->x;
	mob->dstrect.y = mob->y;
	mob->dstrect.w = width;
	mob->dstrect.h = height;

	return mob;
}
