#include <state.h>
#include <wmalloc.h>
namespace game1 {

const char *game_name = "game1";
const int NR_SEL = 4;

State *menu;
State *start;
State *rules; 
State *settings;

void menu_render(State *s) {

}

void render(State *s) {

}

void rules_render(State *s) {

}

void settings_render(State *s) {

}

void init() {
	start = new State(NULL, 0, 0, render, STATE_GAME, game_name);	
	ptr_manager.add(start, MENU_PTR);
	rules = new State(NULL, 0, 0, rules_render, STATE_COMMON, "rules");	
	ptr_manager.add(rules, MENU_PTR);
	settings = new State(NULL, 0, 0, settings_render, STATE_MENU, "settings");	
	ptr_manager.add(settings, MENU_PTR);

	State **menu_menus = (State **)wmalloc(sizeof(State *) * NR_SEL);
	menu_menus[0] = start;
	menu_menus[1] = rules;
	menu_menus[2] = settings;

	menu = new State(menu_menus, 4, 0, menu_render, STATE_MENU, "game1 menu");	
	ptr_manager.add((void*)menu, MENU_PTR);
}











}