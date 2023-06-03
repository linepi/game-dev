#ifndef MENULIST_H
#define MENULIST_H

#include <defs.h>
#include <utils.h>
#include <color.h>
#include <wmalloc.h>

#define TITLE_COLOR white
#define ITEMS_COLOR white
#define ITEMS_COLOR_CHOSEN yellow

// 屏幕高与条目高之比
#define WINDOW_H_ITEMS_RATE (2 * this->nr_selection + 5) 
// 条目间距与条目高之比
#define ITEMS_SPACE_RATE 0.75
// 标题大小与条目大小之比
#define TITLE_ITEMS_RATE 2
// 标题与第一条条目间距与条目高之比
#define TITLE_ITEMS_SPACE_RATE 1.5

class MenuList {
public:
	SDL_Texture **tex;	
	SDL_Surface **sur;	
	SDL_Texture **tex_chosen;	
	SDL_Surface **sur_chosen;	
	int *x;
	int *y;

	int items_size;
	int title_size;

	bool has_title;
	int cur_selection;
	int nr_selection;
	MenuList(
		const char *title_font_path, 
		const char *title_name,
		const char *items_font_path, 
		const char **items_name, 
		int nr_selection
	) {
		this->nr_selection = nr_selection;
		this->cur_selection = 0;
		this->has_title = false;
		if (title_font_path) {
			this->has_title = true;
		}

		// 计算条目字体大小以及标题字体大小
		if (this->has_title == false) { // 如果无标题，则是文字描述
			this->items_size = WINDOW_H / 30;
		} else {
			this->items_size = WINDOW_H / WINDOW_H_ITEMS_RATE;
		}
		this->title_size = this->has_title ? TITLE_ITEMS_RATE * this->items_size : 0;
		// 计算渲染的位置
		x = (int *)wmalloc(sizeof(int) * (this->nr_selection + 1));
		y = (int *)wmalloc(sizeof(int) * (this->nr_selection + 1));
		/* 以下讨论的都是垂直距离上的 */
		// 条目间距
		int items_spacing = this->items_size * ITEMS_SPACE_RATE;
		// 标题条目间距
		int title_items_spacing = this->has_title ? this->items_size * TITLE_ITEMS_SPACE_RATE : 0;
		// 窗口上沿与标题间距(默认此间距与“窗口下沿与最后条目”间距相同)
		int windowtip_title_spacing = (
			WINDOW_H 
			- this->title_size 
			- title_items_spacing 
			- this->nr_selection * this->items_size 
			- items_spacing * (this->nr_selection - 1)
		) / 2;
		// 条目起始位置
		int items_start = windowtip_title_spacing + this->title_size + title_items_spacing;
		/* 以上讨论的都是垂直距离上的 */
		for (int i = !has_title; i < this->nr_selection + 1; i++) {
			if (i == 0) {
				y[i] = windowtip_title_spacing;
			} else {
				y[i] = items_start + (i - 1) * (this->items_size + items_spacing);
			}
		}

		// 分配内存，比条目数大一
		this->tex = (SDL_Texture **)wmalloc(sizeof(SDL_Texture *) * (this->nr_selection + 1));
		this->sur = (SDL_Surface **)wmalloc(sizeof(SDL_Surface *) * (this->nr_selection + 1));
		this->tex_chosen = (SDL_Texture **)wmalloc(sizeof(SDL_Texture *) * (this->nr_selection + 1));
		this->sur_chosen = (SDL_Surface **)wmalloc(sizeof(SDL_Surface *) * (this->nr_selection + 1));

		// 创建标题字体surface & texture
		if (title_font_path) {
			this->sur[0] = get_font(title_font_path, this->title_size, title_name, TITLE_COLOR);
			ptr_manager.add(this->sur[0], SURFACE_PTR);	
			this->tex[0] = SDL_CreateTextureFromSurface(renderer, this->sur[0]);
			ptr_manager.add(this->tex[0], TEXTURE_PTR);
			this->sur_chosen[0] = NULL;
			this->tex_chosen[0] = NULL;
		}
		// 创建条目的字体以及被选中的字体的surface & texture
		for (int i = 0; i < this->nr_selection; i++) {
			this->sur[i+1] = get_font(items_font_path, this->items_size, items_name[i], ITEMS_COLOR);
			ptr_manager.add(this->sur[i+1], SURFACE_PTR);	
			this->tex[i+1] = SDL_CreateTextureFromSurface(renderer, this->sur[i+1]);
			ptr_manager.add(this->tex[i+1], TEXTURE_PTR);

			this->sur_chosen[i+1] = get_font(items_font_path, this->items_size, items_name[i], ITEMS_COLOR_CHOSEN);
			ptr_manager.add(this->sur_chosen[i+1], SURFACE_PTR);	
			this->tex_chosen[i+1] = SDL_CreateTextureFromSurface(renderer, this->sur_chosen[i+1]);
			ptr_manager.add(this->tex_chosen[i+1], TEXTURE_PTR);
		}

		// 字体宽出来了后，开始计算x
		for (int i = !has_title; i < this->nr_selection + 1; i++) {
			// 屏幕大小应该大于字块宽
			assert(WINDOW_W > this->sur[i]->w);
			x[i] = (WINDOW_W - this->sur[i]->w) / 2; 
		}
	}
	void render();
};

#endif