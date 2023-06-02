#ifndef STATE_H
#define STATE_H
#include <defs.h>
#include <debug.h>

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
	const char *name;
	int type;
	State **menus;

	State(State **menus, int nr_selection, int cur_selection, void (*render_func)(State *), int type, const char *name) {
		this->nr_selection = nr_selection;
		this->cur_selection = cur_selection;

		this->menus = menus;
		this->name = name;
		this->type = type;
		this->render_func = render_func;
	}
	void render();
	bool has_render();
	bool ismenu();
	void prev_select();
	void next_select();
	State *choose();
};

error_t menu_init();

#endif