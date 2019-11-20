#include <vector>
#include <iostream>
#include "SDL.h"

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a=255) {
    return (a<<24) + (b<<16) + (g<<8) + r;
}

void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) {
    r = (color >>  0) & 255;
    g = (color >>  8) & 255;
    b = (color >> 16) & 255;
    a = (color >> 24) & 255;
}


bool load_texture(const std::string filename, const uint32_t format, int &tw, int &th, std::vector<uint32_t> &img) {
    SDL_Surface *tmp = SDL_LoadBMP(filename.c_str());
    if (!tmp) {
        std::cerr << "Error in SDL_LoadBMP: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(tmp, format, 0);
    SDL_FreeSurface(tmp);
    if (!surface) {
        std::cerr << "Error in SDL_ConvertSurfaceFormat: " << SDL_GetError() << std::endl;
        return false;
    }

    int w = surface->w;
    int h = surface->h;

    if (w*4!=surface->pitch) {
        std::cerr << "Error: the texture must be a 32 bit image" << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }
    tw = w;
    th = h;
    uint8_t *pixmap = reinterpret_cast<uint8_t *>(surface->pixels);

    img = std::vector<uint32_t>(w*h);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            uint8_t r = pixmap[(i+j*w)*4+0];
            uint8_t g = pixmap[(i+j*w)*4+1];
            uint8_t b = pixmap[(i+j*w)*4+2];
            uint8_t a = pixmap[(i+j*w)*4+3];
            img[i+j*w] = pack_color(r, g, b, a);
        }
    }
    SDL_FreeSurface(surface);
    return true;
}


int main() {
	std::vector<uint32_t> tex_pixels;
	int tex_width, tex_height;
	const std::string tex_file("../herbes.bmp");
	if (!load_texture(tex_file, SDL_PIXELFORMAT_ABGR8888, tex_width, tex_height, tex_pixels)) {
		return -1;
	}


	const int width = 1024;
	const int height = 512;
	std::vector<uint32_t> pixels(width*height, pack_color(255, 255, 255));

	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window   *window   = nullptr;
	SDL_Renderer *renderer = nullptr;

	if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
		std::cerr << "Failed to create window and renderer: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Texture *framebuffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (!framebuffer_texture) {
		std::cerr << "Failed to create framebuffer texture : " << SDL_GetError() << std::endl;
		return -1;
	}	

	for (int j=0; j<height; j++) {
		for (int i=0; i<width; i++) {
			pixels[i+j*width] = pack_color((255*i)/width, (255*j)/height, 0);
		}
	}

	int tex_pos_x = 0;
	int tex_pos_y = 0;
	while (tex_pos_x < width) {
		while(tex_pos_y < height) {
			for (int j=0; j<tex_height; j++) {
				for (int i=0; i<tex_width; i++) {
					pixels[tex_pos_x+i+(j+tex_pos_y)*width] = tex_pixels[i+j*tex_width];
				}
			}
			tex_pos_y = tex_pos_y + 32;
		}
		tex_pos_x = tex_pos_x + 32;
		tex_pos_y = 0;
	}

	while (1) {
		{ // poll events
			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				if (SDL_QUIT==event.type || (SDL_KEYDOWN==event.type && SDLK_ESCAPE==event.key.keysym.sym)) break;
			}
		}
		{ // copy the framebuffer contents to the screen
			SDL_UpdateTexture(framebuffer_texture, NULL, reinterpret_cast<void *>(pixels.data()), width*4);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, framebuffer_texture, NULL, NULL);
			SDL_RenderPresent(renderer);
		}
	}

	{ // save the BMP file
		SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels.data(), width, height, 4, width*4, SDL_PIXELFORMAT_ABGR8888);
		if (!surface) {
			SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
			return -1;
		}
		int res = SDL_SaveBMP(surface, "test.bmp");
		if (res) {
			SDL_Log("Failed saving image: %s\n", SDL_GetError());
			return -1;
		}
		SDL_FreeSurface(surface);
	}

	return 0;
}

