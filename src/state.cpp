#include <defs.h>
#include <color.h>
#include <utils.h>
#include <debug.h>
#include <state.h>
#include <menulist.h>
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
		cur_selection == nr_selection - 1 ?
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

