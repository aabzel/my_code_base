#include "test_evaluate_cache.h"

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "evaluate_cache.h"

bool test_matrix_accsess (void) {
	uint64_t byte = 10000;
	double time_s, time_f;

	for(byte=K_BYTE; byte<G_BYTE;byte*=2){
	    time_f=measure_byte_assess_time_fast_dyn(byte);
    	time_s=measure_byte_assess_time_slow_dyn( byte);
    	if(time_s < time_f){
    		printf("\n Error ft %f st %f",time_f,time_s);
	        return false;
	    }
    	printf("\n%u ft %f st %f",byte ,time_f,time_s);
	}
	return true;
}

 
