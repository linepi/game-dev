#ifndef __DEFS_H__
#define __DEFS_H__

#include <debug.h>
#include <stdio.h>
#include <assert.h>
#include <state.h>
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* main.h */
extern class State *cur_state;
extern bool quit; 
extern int fps;
void render();
void update();
void event_loop();

/* config.h */
struct config {
	int window_w;
	int window_h;
	int fps;
	bool debug;
};

extern struct config game_config;
#define WINDOW_W game_config.window_w
#define WINDOW_H game_config.window_h
error_t config_init();
extern const char *mouse_ttf_path;
extern const char *menu_ttf_path;
extern const char *text_ttf_path;

/* init.h */
#define FONT_POOL_SIZE 200

struct font_pool_t {
	TTF_Font *font;
	const char *path;
	int size;
};

void game_init();
extern SDL_Window* window;
extern SDL_Surface* sur_screen;
extern SDL_Renderer* renderer;
extern SDL_Rect rect_window;


#endif