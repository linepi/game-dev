#include <defs.h>
#include <wmalloc.h>
#include <state.h>

PtrManager::PtrManager() {
	head = (struct ptr_node *)calloc(1, sizeof(struct ptr_node));
}

PtrManager::~PtrManager() {
	struct ptr_node *p = head->next;
	struct ptr_node *pre = head;

	while (p) {
		switch (p->type) {
		case COMMON_PTR:
			free(p->ptr_to_free);
			break;
		case TTF_PTR:
			TTF_CloseFont((TTF_Font*)p->ptr_to_free);
			break;
		case SURFACE_PTR:
			SDL_FreeSurface((SDL_Surface*)p->ptr_to_free);
			break;
		case TEXTURE_PTR:
			SDL_DestroyTexture((SDL_Texture*)p->ptr_to_free);
			break;
		case MENU_PTR:
			delete (State *)p->ptr_to_free;
			break;
		default:
			exit(UNKNOWN_PTR_CASE);
		}
		pre = p;
		p = p->next;	
		free(pre);
	}
	free(head);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void PtrManager::add(void *ptr, int type) {
	struct ptr_node *new_node = (struct ptr_node *)malloc(sizeof(struct ptr_node));
	new_node->ptr_to_free = ptr;
	new_node->type = type;
	new_node->next = head->next;
	head->next = new_node;
}

PtrManager ptr_manager;

void *wmalloc(size_t size) {
	void *ret = malloc(size);	
	ptr_manager.add(ret, COMMON_PTR);
	return ret;
}