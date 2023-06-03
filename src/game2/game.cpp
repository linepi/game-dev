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

// 游戏渲染部分
void game_render(State *s) {
}

// 游戏规则展示部分
void rules_render(State *s) {
	static const char *items_name[] = {
		"This is the rule of " GAME_NAME,
	};
	int nr_selection = sizeof(items_name) / sizeof(char *);
	static MenuList rules(NULL, NULL, text_ttf_path, items_name, nr_selection);
	rules.render();	
}

// 游戏事件更新部分
State* game_event_update(State* s, SDL_Event *e) {
	State *new_state;
	new_state = common_event_update(s, e);
	return new_state;
}

// 游戏的更新部分
void game_update(State *s) {

}

// 游戏的设置部分
void settings_render(State *s) {

}

void init() {
	menu = new State(NULL, 4, 0, menu_render, STATE_MENU, "game2 menu");	
	ptr_manager.add(menu, MENU_PTR);
	menu->set_event_update(menu_event_update);

	// 这是游戏状态
	start = new State(NULL, 0, 0, game_render, STATE_GAME, game_name);	
	ptr_manager.add(start, MENU_PTR);
	start->set_event_update(game_event_update);
	start->set_update(game_update);
	start->prev = menu;

	rules = new State(NULL, 0, 0, rules_render, STATE_COMMON, "rules");	
	ptr_manager.add(rules, MENU_PTR);
	rules->prev = menu;

	settings = new State(NULL, 0, 0, settings_render, STATE_MENU, "settings");	
	ptr_manager.add(settings, MENU_PTR);
	settings->prev = menu;
	settings->set_event_update(menu_event_update);

	State **menu_menus = (State **)wmalloc(sizeof(State *) * NR_SEL);
	menu_menus[0] = start;
	menu_menus[1] = rules;
	menu_menus[2] = settings;
	menu->menus = menu_menus;
}








}