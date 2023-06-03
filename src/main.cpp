#include <defs.h>
#include <debug.h>
#include <utils.h>
#include <color.h>
#include <state.h>
#include <game1/game.h>
#include <game2/game.h>

int main(int argc, char* args[]) {
	game_init();
	uint32_t last = SDL_GetTicks();
	int frames = 0;
	while (!quit) { 
		uint32_t loop_start_ms = SDL_GetTicks();
		event_loop();	
		update();
		render();
		// about fps
		uint32_t loop_end_ms = SDL_GetTicks();
		uint32_t cost = loop_end_ms - loop_start_ms;
		uint32_t frame_ms = 1000 / game_config.fps;
		uint32_t sleep_ms = frame_ms > cost ? frame_ms - cost : 0;
		frames++;
		if (loop_end_ms - last >= (uint32_t)1000) {
			last = loop_end_ms;
			fps = frames;
			frames = 0;
			printf("fps: %d\n", fps);
		}
		SDL_Delay(sleep_ms);
	}
	SDL_DestroyWindow(window);
	return 0;
}

void update() {
	if (cur_state->has_update()) 
		cur_state->update(); 
}

void render() {
	assert(cur_state);
	assert(cur_state->has_render());
	cur_state->render();
	SDL_RenderPresent(renderer);	
}

void event_loop() {
	SDL_Event e; 
	while (SDL_PollEvent(&e)) { 
		if (cur_state->has_event_update())
			cur_state = cur_state->event_update(&e);
	} 
}