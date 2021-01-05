// hello.cpp
#include <iostream>

#include "uTests.h"
#include "test_intervals.h"
#include "test_brick_wall.h"

using namespace std;
 
static size_t basename_start_calc(const char* filename){
    const char* base = strrchr(filename, '/');
    return base ? (base - filename + 1) : 0;
}

size_t basename_start(const char* filename){
    static size_t retval = basename_start_calc(filename);
    return retval;
}

//#define STR_(t) #t
//#define STR(t) STR_(t)
#define BASENAME()  ((__FILE__ ":") + basename_start(__FILE__))




int init_by_foo3(void){
	cout <<__FUNCTION__<<"() line "<<__LINE__ << endl;
	return 3;
}

int init_by_foo4(void){
	cout <<__FUNCTION__<<"() line "<<__LINE__ << endl;
	return 4;
}

int a_val3=init_by_foo3();
int a_val4=init_by_foo4();




bool u_tests(void) {
   cout << "u_tests" << endl;
   EXPECT_TRUE( test_brick_wall( ));
   EXPECT_TRUE( test_remove_Covered_Intervals( ));
   cout << "u_tests fine" << endl;
   return true;
}
