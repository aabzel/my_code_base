#include "evaluate_cache.h"

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool inctement_matrix_slow(uint8_t *arr, int col, int row) {
	bool res = false;
	if (arr) {
		res = true;
		for (int j = 0; j < row; j++) {
			for (int i = 0; i < col; i++) {
				(*(arr + row * i + j))++;
			}
		}
	}
	return res;
}
//static uint8_t arr[MEM_SIZE_BYTE];

static uint64_t rand_uint64_slow(void) {
	uint64_t r = 0;
	for (int i = 0; i < 64; i++) {
		r = r * 2 + rand() % 2;
	}
	return r;
}

//512
static double measure_byte_assess_time_dyn(uint64_t byte) {
	//int col = sqrt(byte); //16
	double time_taken = -1.0;
	clock_t start;

	//int row = byte /col;
	if (0 < byte) {
#ifdef DEBUG_RESULT
		printf("\n row %u col %u \n", row, col);
#endif
		uint8_t *arr = (uint8_t*) malloc(byte);
		if (arr) {
			memset(arr, 0x00, byte);
			start = clock();
			//inctement_matrix_slow(arr, col, row);
#if 1
			for (int i = 0; i < byte; i++) {
#ifdef DEBUG_RESULT
				printf("\n [%u][%u] byte %lu ", i,j, byte);
#endif
				uint64_t index = 0;
				//int index =  col * i + j;
				index = rand_uint64_slow() % byte;
#ifdef DEBUG_RESULT
				printf("\n index [%lu] byte %lu ", index, byte);
#endif
				if (index < byte) {
					(*(arr + index))++;
				} else {
					printf("\n  index %lu too big (%lu) ", index,
							MEM_SIZE_BYTE);
				}
			}

#endif
			time_taken = (double) (clock() - start);
			free(arr);
			arr = NULL;
		} else {
			printf("\n  unable to alloc %lu byte ", byte);
		}
	}
	return (time_taken / (double) byte);
}

double measure_byte_assess_time_fast_dyn(uint64_t byte) {
	int col = sqrt(byte); //16
	double time_taken = -1.0;
	clock_t start;

	int row = byte / col;
	if ((0 < col) && (0 < row)) {
#ifdef DEBUG_RESULT
		printf("\n row %u col %u \n", row, col);
#endif
		uint8_t *arr = (uint8_t*) malloc(byte);
		if (arr) {
			memset(arr, 0x01, byte);
			start = clock();
			//inctement_matrix_slow(arr, col, row);
			for (uint64_t i = 0; i < col; i++) {
				for (uint64_t j = 0; j < row; j++) {
#ifdef DEBUG_RESULT
				printf("\n [%u][%u] byte %lu ", i,j, byte);
#endif
					uint64_t index = 0;
					index = col * i + j;

#ifdef DEBUG_RESULT
				printf("\n index [%lu] byte %lu ", index, byte);
#endif
					if (index < byte) {
						(*(arr + index)) *= 10;
						(*(arr + index)) /= 5;
					} else {
						printf("\n  index %lu too big (%lu) ", index,
								MEM_SIZE_BYTE);
					}
				}
			}

			time_taken = (double) (clock() - start);
			free(arr);
			arr = NULL;
		} else {
			printf("\n  unable to alloc %lu byte ", byte);
		}
	}
	return (time_taken / (double) byte);
}

double measure_byte_assess_time_slow_dyn(uint64_t byte) {
	int col = sqrt(byte); //16
	double time_taken = -1.0;
	clock_t start;

	int row = byte / col;
	if ((0 < col) && (0 < row)) {
#ifdef DEBUG_RESULT
		printf("\n row %u col %u \n", row, col);
#endif
		uint8_t *arr = (uint8_t*) malloc(byte);
		if (arr) {
			memset(arr, 0x01, byte);
			start = clock();
			//inctement_matrix_slow(arr, col, row);

			for (uint64_t j = 0; j < row; j++) {
				for (uint64_t i = 0; i < col; i++) {
#ifdef DEBUG_RESULT
				printf("\n [%u][%u] byte %lu ", i,j, byte);
#endif
					uint64_t index = 0;
					index = col * i + j;

#ifdef DEBUG_RESULT
				printf("\n index [%lu] byte %lu ", index, byte);
#endif
					if (index < byte) {

						(*(arr + index)) *= 10;
						(*(arr + index)) /= 5;
					} else {
						printf("\n  index %lu too big (%lu) ", index,
								MEM_SIZE_BYTE);
					}
				}
			}

			time_taken = (double) (clock() - start);
			free(arr);
			arr = NULL;
		} else {
			printf("\n  unable to alloc %lu byte ", byte);
		}
	}
	return (time_taken / (double) byte);
}

#ifdef STAT
//512
double measure_byte_assess_time_stat(uint32_t byte) {
	int col = sqrt(byte); //16
	double time_taken = -1.0;
	clock_t start;

	int row = byte /col;
	if ((0 < row) && (0 < col)) {
#ifdef DEBUG_RESULT
		printf("\n row %u col %u \n", row, col);
#endif
		memset(arr, 0x00, byte);
		start = clock();
		//inctement_matrix_slow(arr, col, row);
#if 1
		for (int k = 0; k < 1; k++) {

		for (int j = 0; j < row; j++) {
    		for (int i = 0; i < col; i++) {
#ifdef DEBUG_RESULT
					printf("\n [%u][%u] byte %u ", i,j, byte);
#endif
					int index =  col * i + j;
					if(index<MEM_SIZE_BYTE){
    					(*(arr + index))++;
					}else{
						printf("\n  index %u too big (%u) ", index, MEM_SIZE_BYTE);
					}
				}
			}
		}
#endif
		time_taken = (double) (clock() - start) ;
	}
	return (time_taken /(double)  byte);
}
#endif /*STAT*/

//https://stackoverflow.com/questions/21299488/cache-size-estimation-on-your-system
bool evaluate_cache(uint64_t byte_max) {
	uint64_t byte;
	double time_to_byte;
	FILE *fp;
	char file_out_name[100];
	snprintf(file_out_name, sizeof(file_out_name),
			"ram_access_time_%lu_step_%u.txt", MEM_SIZE_BYTE, SIZE_STEP);
	printf("\n CLOCKS_PER_SEC %u ", CLOCKS_PER_SEC);
	for (byte = 2; byte < MEM_SIZE_BYTE; byte *= 1.5) {
		time_to_byte = measure_byte_assess_time_dyn(byte);
		if (0.0 < time_to_byte) {
			printf(",");
			//if(0==byte%((MEM_SIZE_BYTE/SIZE_STEP)/100)){
			//	printf("\n done %f",((double )byte/(double )MEM_SIZE_BYTE));
			//}
			fp = fopen(file_out_name, "a");
			if (NULL != fp) {
				fprintf(fp, "\n%lu  %f", byte, time_to_byte);
				fclose(fp);
			} else {
				printf("\n Unable to open file");
			}
#ifdef DEBUG_RESULT
				printf("\n kByte %u time %f", byte, time_to_byte);
#endif /*DEBUG_ERROR*/
		} else {
			printf("\n.");
#ifdef DEBUG_ERROR
				printf("\n invalid  time_to_byte %f for byte %u", time_to_byte,
						byte);
#endif /*DEBUG_ERROR*/
		}
	}
	return true;
}
