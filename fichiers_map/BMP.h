#ifndef _BMP_H
#define _BMP_H

typedef struct Pixel
{
	unsigned char r,g,b;
} Pixel;

typedef struct Image
{
	int w,h;
	Pixel* dat;
} Image;

Image* Charger(const char* fichier);
int Sauver(Image*, const char* fichier);
Image* NewImage(int w, int h);
Image* CopieImage(Image* I);
void SetPixel(Image* I, int i, int j, Pixel p);
Pixel GetPixel(Image* I, int i, int j);
void DelImage(Image* I);

#endif
