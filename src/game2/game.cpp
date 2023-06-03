#include <state.h>
#include <wmalloc.h>
#include <menulist.h>

namespace game2 {

const char *game_name = "game2";
#define GAME_NAME "game2"

const int NR_SEL = 4;
State *menu;
State *start;
State *rules; 
State *settings;

void menu_render(State *s) {
	static const char *items_name[] = {
		"start",
		"rules",
		"settings",
		"back"
	};
	static MenuList menulist(menu_ttf_path, game_name, menu_ttf_path, items_name, NR_SEL);
	menulist.cur_selection = s->cur_selection;
	menulist.render();
}

void render(State *s) {

}

void rules_render(State *s) {
	static const char *items_name[] = {
		"This is the rule of " GAME_NAME
	};
	int nr_selection = sizeof(items_name) / sizeof(char *);
	static MenuList rules(NULL, NULL, text_ttf_path, items_name, nr_selection);
	rules.render();
}

void settings_render(State *s) {

}

void init() {
	menu = new State(NULL, 4, 0, menu_render, STATE_MENU, "game2 menu");	
	ptr_manager.add(menu, MENU_PTR);

	start = new State(NULL, 0, 0, render, STATE_GAME, game_name);	
	ptr_manager.add(start, MENU_PTR);
	start->prev = menu;

	rules = new State(NULL, 0, 0, rules_render, STATE_COMMON, "rules");	
	ptr_manager.add(rules, MENU_PTR);
	rules->prev = menu;

	settings = new State(NULL, 0, 0, settings_render, STATE_MENU, "settings");	
	ptr_manager.add(settings, MENU_PTR);
	settings->prev = menu;

	State **menu_menus = (State **)wmalloc(sizeof(State *) * NR_SEL);
	menu_menus[0] = start;
	menu_menus[1] = rules;
	menu_menus[2] = settings;
	menu->menus = menu_menus;
}









}