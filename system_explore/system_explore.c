#include "system_explore.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

bool test_free_zero(void) {
	printf("\n[d] %s()", __FUNCTION__);
    free(NULL);
	return true;
}

bool test_malloc_zero(void) {
	printf("\n[d] %s()", __FUNCTION__);
	bool res = false;
	char *ptr = malloc(0);
	if (NULL != ptr) {
		res = false;
		free(ptr);
	} else {
		res = true;
	}
	return res;
}

bool test_malloc(void) {
	printf("\n[d] %s()", __FUNCTION__);
	bool res = false;
	char *ptr = malloc(100);
	if (NULL != ptr) {
		memset(ptr, 0x00, 100);
		printf("\n sizeof(ptr) %d \n", sizeof(ptr)); // 4
		printf("\n msize(ptr) %d \n", _msize(ptr));  // 100
		if (100 == _msize(ptr)) {
			res = true;
		}
		free(ptr);
	}
	return res;
}

bool work_with_stack(int n, uint8_t pat) {
	printf("\n[d] %s()", __FUNCTION__);
	// uint8_t array[n];
	bool res = false;
	uint8_t *array = alloca(n);
	if (array) {
		memset(array, pat, n);
		if (is_arr_pat(array, n, pat)) {
			res = true;
		}
	}
	return res;
}

bool test_static(void) {
	printf("\n[d] %s()", __FUNCTION__);
	static int a;
	printf("\n static a a=%d &a=%p", a, &a);
	bool res = false;
	if (0 == a) {
		res = true;
	}
	a++;
	return res;
}

bool test_heap(void) {
	printf("\n[d] %s()", __FUNCTION__);
	uint32_t byte = 3;
	uint32_t mult = 10;
	uint32_t div = 2;
	while (1) {
		char *ptr = NULL;
		ptr = (char*) malloc(byte);
		if (ptr) {
			byte = (byte * mult) / div;
			// print_bytes (byte);
			free(ptr);
		} else {
			break;
		}
	} //[2327387742]
	print_bytes(byte);

	return true;
}

bool test_heap_set(void) {
	printf("\n[d] %s()", __FUNCTION__);
	uint32_t byte = 3;
	uint32_t mult = 10;
	uint32_t div = 2;
	while (1) {
		char *ptr = NULL;
		ptr = (char*) malloc(byte);
		if (ptr) {
			memset(ptr, 0x00, byte);
			byte = (byte * mult) / div;
			// print_bytes (byte);
			free(ptr);
		} else {
			break;
		}
	} //[2327387742]
	print_bytes(byte);

	return true;
}


#define MAX_ALLOCS 1000000

#if 0
//test_sbrk(1000, 10240, 2,1 )
bool test_sbrk(int argc, char *argv[], int numAllocs, int blockSize, int freeStep, int freeMin, int freeMax) {
	bool res=true;
	char *ptr[MAX_ALLOCS];
	int j;
	printf("\n");

	if (numAllocs > MAX_ALLOCS){
		printf("[e] num-allocs > %d\n", MAX_ALLOCS);
		return false;
	}
	//freeMin = 1;
	//freeMax =   numAllocs;
	if (freeMax > numAllocs){
		printf("[e] free-max > num-allocs\n");
		return false;
		res=false;
	}
	printf("Initial program break: %10p\n", sbrk(0));
	printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
	for (j = 0; j < numAllocs; j++) {
		ptr[j] = malloc(blockSize);
		if (ptr[j] == NULL){
			printf("[e] malloc");
			return false;
			res=false;
		}
	}
	printf("Program break is now: %10p\n", sbrk(0));
	printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax,
			freeStep);
	for (j = freeMin - 1; j < freeMax; j += freeStep){
		free(ptr[j]);
	}
	printf("After free(), program break is: %10p\n", sbrk(0));
	return res;
}
#endif

