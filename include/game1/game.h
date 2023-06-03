#ifndef GAME1_H
#define GAME1_H
#include <state.h>
namespace game1 {

extern const char *game_name;
void menu_render(State *s);
void game_render(State *s);
void rules_render(State *s);
void settings_render(State *s);
void init();
extern State *menu; 
extern State *start; 
extern State *rules; 
extern State *settings;






















}
#endif