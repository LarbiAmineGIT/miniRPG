#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BMP.h"

Image* NewImage(int w, int h)
{
	Image* I = malloc(sizeof(Image));
	I->w = w;
	I->h = h;
	I->dat = calloc(1,w*h*sizeof(Pixel*));
	return I;
}

Image* CopieImage(Image* I)
{
	Image* res;
	if(!I){
		return NULL;
	}
	res = NewImage(I->w, I->h);
	memcpy(res->dat, I->dat, I->w*I->h*sizeof(Pixel));
	return res;
}

void DelImage(Image* I)
{
	if(I) {
		free(I->dat);
		free(I);
	}
}

void SetPixel(Image* I, int i, int j, Pixel p)
{
	assert(I && i>=0 && i<I->w && j>=0 && j<I->h);
	I->dat[I->w*j + j] = p;
}

Pixel GetPixel(Image* I, int i, int j)
{
	assert(I && i>= 0 && i<I->w && j>= 0 && j<I->h);
	return I->dat[I->w*j+i];
}

//-------

#pragma pack(1) //Désactive l'alignement mémoire
typedef int int32;
typedef short int16;

struct BMPImHead
{
	int32 size_imhead;
	int32 width;
	int32 height;
	int16 nbplans;
	int16 bpp;
	int32 compression;
	int32 sizeim;
	int32 hres;
	int32 vres;
	int32 cpalette;
	int32 cIpalette;
};

struct BMPHead
{
	char signature[2];
	int32 taille;
	int32 rsv;
	int32 offsetim;
	struct BMPImHead imhead;
};

Image* Charger(const char* fichier)
{
	struct BMPHead head;
	Image* I;
	int i,j,pitch;
	unsigned char bgrpix[3];
	char corrpitch[4] = {0,3,2,1};
	Pixel p;
	FILE* F = fopen(fichier,"rb");
	if(!F){
		return NULL;
	}
	fread(&head, sizeof(struct BMPHead),1,F);
	if(head.signature[0]!='B' || head.signature[1] != 'M'){
		return NULL;
	}
	if(head.imhead.bpp != 24){
		return NULL;
	}
	if(head.imhead.compression != 0) {
		return NULL;
	}
	if(head.imhead.cpalette != 0) {
		return NULL;
	}
	I = NewImage(head.imhead.width, head.imhead.height);
	pitch = corrpitch[(3*head.imhead.width)%4];
	for(j=0 ; j<I->h ; j++)
	{
		for(i = 0 ; i < I->w ; i++) {
			fread(&bgrpix,1,3,F);
			p.r = bgrpix[2];
			p.g = bgrpix[1];
			p.b = bgrpix[0];
			SetPixel(I,i,I->h-j-1,p);
		}
		fread(&bgrpix, 1, pitch, F);
	}
	fclose(F);
	return I;
}

int Sauver(Image* I, const char* fichier)
{
	struct BMPHead head;
	Pixel p;
	int i,j,tailledata,pitch;
	unsigned char bgrpix[3];
	char corrpitch[4] = {0,3,2,1};
	FILE* F = fopen(fichier, "wb");
	if(!F) {
		return -1;
	}
	memset(&head,0,sizeof(struct BMPHead));
	head.signature[0] = 'B';
	head.signature[1] = 'M';
	head.offsetim = sizeof(struct BMPHead);
	head.imhead.size_imhead = sizeof(struct BMPImHead);
	head.imhead.width = I->w;
	head.imhead.height = I->h;
	head.imhead.nbplans = 1;
	head.imhead.bpp = 24;
	pitch = corrpitch[(3*head.imhead.width)%4];
	tailledata = 3*head.imhead.height*head.imhead.width + head.imhead.height*pitch;
	head.imhead.sizeim = tailledata;
	head.taille = head.offsetim + head.imhead.sizeim;
	fwrite(&head, sizeof(struct BMPHead),1,F);
	for(j=0 ; j<I->h ; j++)
	{
		for(i=0 ; i<I->w ; i++) {
			p = GetPixel(I,i,I->h-j-1);
			bgrpix[0] = p.b;
			bgrpix[1] = p.g;
			bgrpix[2] = p.r;
			fwrite(&bgrpix,1,3,F);
		}
		bgrpix[0] = bgrpix[1] = bgrpix[2] = 0;
		fwrite(&bgrpix, 1, pitch, F);
	}
	fclose(F);
	return 0;
}

