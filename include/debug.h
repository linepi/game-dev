#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <dbg.h>

enum {
	NO_ERROR,
	FILE_OPEN_ERROR,
	MALLOC_ERROR,
	UNKNOWN_PTR_CASE
};

typedef int error_t;
extern error_t error;

#endif