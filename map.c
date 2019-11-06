/*
author : Mireille Vignal
date : 18/09/2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "BMP.h"

int main()
{
	int i,j;
	Image* I = NewImage(256,256);
	for(i=0 ; i<256 ; i++)
	{
		for(j=0 ; j<256 ; j++) {
			Pixel p;
			p.r = i;
			p.g = j;
			p.b = 0;
			SetPixel(I,i,j,p);
		}
	}

	Sauver(I, "test.bmp");
	DelImage(I);
	return 0;
}

