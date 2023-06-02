#ifndef WMALLOC_H
#define WMALLOC_H

#include <stdlib.h>

enum {
	COMMON_PTR,
	TTF_PTR,
	SURFACE_PTR,
	TEXTURE_PTR,
	MENU_PTR
};

struct ptr_node {
	void *ptr_to_free;
	int type;
	struct ptr_node *next;
};

class PtrManager {
private:
	struct ptr_node *head; 	
public:
	PtrManager();
	~PtrManager();
	void add(void* ptr, int type);
};


extern PtrManager ptr_manager;
void *wmalloc(size_t size);

#endif