#include <menulist.h>
#include <state.h>
#include <wmalloc.h>
#include <defs.h>
#include <game1/game.h>
#include <game2/game.h>

void MenuList::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	int start = !has_title;
	for (int j = start; j < nr_selection + 1; j++) {
		// 无标题说明不是menu，渲染默认颜色
		if (j != cur_selection + 1 || !has_title)
			SDL_RenderCopy(renderer, tex[j], NULL, rect(x[j], y[j], sur[j]->w, sur[j]->h));
		else
			SDL_RenderCopy(renderer, tex_chosen[j], NULL, rect(x[j], y[j], sur[j]->w, sur[j]->h));
	}
}

#define NR_MAIN_SEL 5
#define NR_SETTINGS_SEL 5

static void main_menu_render(State *s) {
	static const char *items_name[] = {
		game1::game_name,
		game2::game_name,
		"settings",
		"about",
		"quit"
	};
	static MenuList menulist(menu_ttf_path, "Lemonorn World", menu_ttf_path, items_name, NR_MAIN_SEL);
	menulist.cur_selection = s->cur_selection;
	menulist.render();	
}

static void about_render(State *s) {
	static const char *items_name[] = {
		"This is a SDL game application. ",
		"Welcome to github.com/linepi/game-dev and pull request. ",
		"Give your comment and I will glad to make the game better. "
	};
	int nr_selection = sizeof(items_name) / sizeof(char *);
	static MenuList about(NULL, NULL, text_ttf_path, items_name, nr_selection);
	about.render();
}

static void settings_render(State *s) {
}

static void quit_render(State *s) {
}

error_t menu_init() {
	State *main_menu = new State(NULL, NR_MAIN_SEL, 0, main_menu_render, STATE_MENU, "main_menu");
	ptr_manager.add((void*)main_menu, MENU_PTR);
	main_menu->prev = main_menu;

	State *about = new State(NULL, 0, 0, about_render, STATE_COMMON, "about");
	ptr_manager.add((void*)about, MENU_PTR);
	about->prev = main_menu;

	State *settings = new State(NULL, NR_SETTINGS_SEL, 0, settings_render, STATE_MENU, "settings");
	ptr_manager.add((void*)settings, MENU_PTR);
	settings->prev = main_menu;

	State *quit = new State(NULL, 0, 0, quit_render, STATE_QUIT, NULL);
	ptr_manager.add((void*)quit, MENU_PTR);

	State **main_menu_menus = (State **)wmalloc(sizeof(State *) * NR_MAIN_SEL);
	main_menu_menus[0] = game1::menu;
	main_menu_menus[1] = game2::menu;
	main_menu_menus[2] = settings;
	main_menu_menus[3] = about;
	main_menu_menus[4] = quit;
	main_menu->menus = main_menu_menus;

	// go back
	game1::menu->menus[3] = main_menu;
	game2::menu->menus[3] = main_menu;

	game1::menu->prev = main_menu;
	game2::menu->prev = main_menu;
	// the cur_state is main_menu
	cur_state = main_menu;
	return NO_ERROR;
}