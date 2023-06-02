#ifndef UTIL_H
#define UTIL_H

#include <defs.h>

SDL_Rect *rect(int x, int y, int w, int h);
SDL_Rect *rect2(int x, int y, int w, int h);
SDL_Color *color(uint8_t, uint8_t, uint8_t, uint8_t);

SDL_Surface *get_image(const char* path);
SDL_Texture *get_image_tex(const char* path);
SDL_Surface *get_font(const char* path, int size, const char *content, SDL_Color color);
SDL_Texture *get_font_tex(const char* path, int size, const char *content, SDL_Color color);


#endif