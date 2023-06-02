#include <defs.h>
#include <wmalloc.h>
#include <state.h>
#include <game1/game.h>
#include <game2/game.h>

SDL_Window* window = NULL;
SDL_Surface* sur_screen = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect rect_window;
State *cur_state = NULL; 
bool quit = false; 
int fps = 0;

void game_init() {
	int img_flags = IMG_INIT_JPG | IMG_INIT_PNG;
	assert(IMG_Init(img_flags) == img_flags);

	assert(TTF_Init() == 0);	

	if ((error = config_init()) != NO_ERROR) exit(error);

	assert(SDL_Init(SDL_INIT_EVERYTHING) >= 0);

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN );
	assert(window);
	SDL_Rect tmp = {.x=0, .y=0, .w=WINDOW_W, .h=WINDOW_H};
	rect_window = tmp;	

	game1::init();
	game2::init();
	if ((error = menu_init()) != NO_ERROR) exit(error);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer);
}

