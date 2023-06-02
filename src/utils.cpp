#include <defs.h>
#include <wmalloc.h>

// temporate color and rect
static SDL_Color __color;
static SDL_Rect __rect;
static SDL_Rect __rect2;

SDL_Rect *rect(int x, int y, int w, int h) {
	__rect.x = x; 
	__rect.y = y; 
	__rect.w = w; 
	__rect.h = h; 
	return &__rect;
}

SDL_Rect *rect2(int x, int y, int w, int h) {
	__rect2.x = x; 
	__rect2.y = y; 
	__rect2.w = w; 
	__rect2.h = h; 
	return &__rect2;
}

SDL_Color *color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	__color.r = r; 
	__color.g = g; 
	__color.b = b; 
	__color.a = a; 
	return &__color;
}

static font_pool_t font_pool[FONT_POOL_SIZE];
static int nr_font = 0;

SDL_Surface* get_image(const char *path) {
	SDL_Surface *loaded = IMG_Load(path);
	if (loaded) ptr_manager.add((void *)loaded, SURFACE_PTR);
	return loaded;
}

SDL_Texture* get_image_tex(const char *path) {
	SDL_Texture *loaded = IMG_LoadTexture(renderer, path);
	if (loaded) ptr_manager.add((void *)loaded, TEXTURE_PTR);
	return loaded;
}

SDL_Surface* get_font(const char *path, int size, const char *content, SDL_Color color) {
	assert(nr_font < FONT_POOL_SIZE);

	TTF_Font *font;
	// get font
	int i;
	for (i = 0; i < nr_font; i++) {
		if (strcmp(path, font_pool[i].path) == 0 && size == font_pool[i].size) {
			font = font_pool[i].font;
			break;
		}
	}
	// no font find
	if (i == nr_font) {
		font = TTF_OpenFont(path, size);
		assert(font);
		ptr_manager.add((void *)font, TTF_PTR);
		// register
		font_pool[nr_font++] = {.font=font, .path=path, .size=size};
	}
	// get surface
	SDL_Surface* sur_font = TTF_RenderUTF8_Blended(font, content, color);
	assert(sur_font);
	return sur_font;
}

SDL_Texture* get_font_tex(const char *path, int size, const char *content, SDL_Color color) {
	SDL_Surface *sur = get_font(path, size, content, color);
	SDL_Texture *res = SDL_CreateTextureFromSurface(renderer, sur);
	if (res) ptr_manager.add((void *)res, TEXTURE_PTR);
	return res;	
}

