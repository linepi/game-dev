#include <defs.h>
#include <color.h>
#include <utils.h>
#include <debug.h>
#include <state.h>
#include <wmalloc.h>
#include <game1/game.h>
#include <game2/game.h>

void State::render() {
	this->render_func(this);
}

void State::prev_select() {
	cur_selection = 
		cur_selection == 0 ? 
		nr_selection - 1: 
		cur_selection - 1;
}

void State::next_select() {
	cur_selection = 
		cur_selection == cur_selection - 1 ?
		0:
		cur_selection + 1;
}

State* State::choose() {
	assert(ismenu());
	State *ret = this->menus[cur_selection];
	if (ret->type == STATE_QUIT) quit = true;
	return ret;
}

bool State::ismenu() {
	return this->menus != NULL && this->type == STATE_MENU;
}

bool State::has_render() {
	return this->render_func != NULL;
}

#define NR_MAIN_SEL 5
#define NR_SETTINGS_SEL 5

static void main_menu_render(State *s) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
	SDL_RenderClear(renderer);
	SDL_Surface *sur_title = get_font("./assets/mouse.ttf", 70, "Lemonorn's World", white);
	SDL_Texture *tex_title = get_font_tex("./assets/mouse.ttf", 70, "Lemonorn's World", white);
	SDL_RenderCopy(renderer, tex_title, NULL, rect2(30, 30, sur_title->w, sur_title->h));
}

static void about_render(State *s) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
	SDL_RenderClear(renderer);
	SDL_Surface *sur_title = get_font("./assets/mouse.ttf", 70, "about", white);
	SDL_Texture *tex_title = get_font_tex("./assets/mouse.ttf", 70, "about", white);
	SDL_RenderCopy(renderer, tex_title, NULL, rect2(30, 30, sur_title->w, sur_title->h));

}

static void settings_render(State *s) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
	SDL_RenderClear(renderer);
	SDL_Surface *sur_title = get_font("./assets/mouse.ttf", 70, "settings", white);
	SDL_Texture *tex_title = get_font_tex("./assets/mouse.ttf", 70, "settings", white);
	SDL_RenderCopy(renderer, tex_title, NULL, rect2(30, 30, sur_title->w, sur_title->h));
}

error_t menu_init() {
	State *main_menu = new State(NULL, NR_MAIN_SEL, 0, main_menu_render, STATE_MENU, "main_menu");
	ptr_manager.add((void*)main_menu, MENU_PTR);

	State *about = new State(NULL, 0, 0, about_render, STATE_COMMON, "about");
	ptr_manager.add((void*)about, MENU_PTR);

	State *settings = new State(NULL, NR_SETTINGS_SEL, 0, settings_render, STATE_MENU, "settings");
	ptr_manager.add((void*)settings, MENU_PTR);

	State *quit = new State(NULL, 0, 0, NULL, STATE_QUIT, NULL);
	ptr_manager.add((void*)quit, MENU_PTR);

	State **main_menu_menus = (State **)wmalloc(sizeof(State *) * NR_MAIN_SEL);
	main_menu_menus[0] = game1::menu;
	main_menu_menus[1] = game2::menu;
	main_menu_menus[2] = settings;
	main_menu_menus[3] = about;
	main_menu_menus[4] = quit;
	main_menu->menus = main_menu_menus;

	// go back
	game1::menu->menus[4] = main_menu;
	game2::menu->menus[4] = main_menu;

	// the cur_state is main_menu
	cur_state = main_menu;
	return NO_ERROR;
}