#ifndef STATE_H
#define STATE_H
#include <defs.h>
#include <SDL2/SDL.h>
#include <debug.h>

class State;
error_t menu_init();
State* menu_event_update(State *s, SDL_Event *e);
State* common_event_update(State *s, SDL_Event *e);

enum {
	STATE_MENU,
	STATE_GAME,
	STATE_COMMON,
	STATE_QUIT
};

class State {
public:
	int nr_selection;
	int cur_selection;
	void (*render_func)(State *);
	void (*update_func)(State *);
	// 事件可能会更改状态，所以返回新状态
	State* (*event_update_func)(State *, SDL_Event *);
	const char *name;
	int type;
	State *prev;
	State **menus;

	State(State **menus, int nr_selection, int cur_selection, void (*render_func)(State *), int type, const char *name) {
		this->nr_selection = nr_selection;
		this->cur_selection = cur_selection;

		this->menus = menus;
		this->name = name;
		this->type = type;
		this->render_func = render_func;
		this->update_func = NULL;
		this->event_update_func = common_event_update;
	}
	// menu 相关
	bool ismenu();
	void prev_select();
	void next_select();
	State *choose();

	// 渲染相关
	bool has_render();
	void render();

	// 更新相关
	void set_update(void (*func)(State *));
	bool has_update();
	void update();

	// 事件相关
	void set_event_update(State* (*func)(State *, SDL_Event *));
	bool has_event_update();
	State* event_update(SDL_Event *e);
};

#endif