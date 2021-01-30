#include "memmgr.h"
#include <string.h>

 
void* malloc(size_t size) {
	#if 0
    return pvPortMalloc(size);
	#endif
	return NULL;
}

void free(void* ptr) {
	#if 0
    vPortFree(ptr);
	#endif
}

void* realloc(void* ptr, size_t size) {
	#if 0
    if(size == 0) {
        vPortFree(ptr);
        return NULL;
    }

    void* p;
    p = pvPortMalloc(size);
    if(p) {
        // TODO implement secure realloc
        // insecure, but will do job in our case
        if(ptr != NULL) {
            memcpy(p, ptr, size);
            vPortFree(ptr);
        }
    }
    return p;
	#endif
	return NULL;
}

void* calloc(size_t count, size_t size) {
	#if 0
    void* ptr = pvPortMalloc(count * size);
    if(ptr) {
        // zero the memory
        memset(ptr, 0, count * size);
    }
    return ptr;
	#endif
	return NULL;
}

char* strdup(const char* s) {
	#if 0
    if(s == NULL) {
        return NULL;
    }

    size_t siz = strlen(s) + 1;
    char* y = malloc(siz);

    if(y != NULL) {
        memcpy(y, s, siz);
    } else {
        return NULL;
    }
    return y;
#endif
	return NULL;
}

size_t memmgr_get_free_heap(void) {
	#if 0
    return xPortGetFreeHeapSize();
	#endif
	return NULL;
}

size_t memmgr_get_minimum_free_heap(void) {
	#if 0
    return xPortGetMinimumEverFreeHeapSize();
	#endif
	return NULL;
}