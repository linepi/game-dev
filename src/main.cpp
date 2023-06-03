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
		switch (e.type) {
		case SDL_QUIT: 
			quit = true; 
			break;
		case SDL_KEYDOWN: 
			if (e.key.keysym.sym == SDLK_q) {
				quit = true;
			}
			switch (e.key.keysym.sym) {
				case SDLK_w: case SDLK_UP:  
					if (cur_state->ismenu())
						cur_state->prev_select();
					break;
				case SDLK_s: case SDLK_DOWN:
					if (cur_state->ismenu())
						cur_state->next_select();
					break;
				case SDLK_a: case SDLK_LEFT:
					break;
				case SDLK_d: case SDLK_RIGHT:
					break;
				case SDLK_RETURN: {
					if (cur_state->ismenu())
						cur_state = cur_state->choose();
					break;
				}
				case SDLK_ESCAPE: {
					cur_state = cur_state->prev;
					break;
				}
			}
			break;
		}
	} 
}