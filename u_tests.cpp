// hello.cpp
#include <iostream>

#include "uTests.h"

#if ALGORITHMS_OOP
#include "test_algorithms_oop.h"
#endif

#if INTERVALS
#include "test_intervals.h"
#endif

#if BRICK_WALL
#include "test_brick_wall.h"
#endif

#if NUMBER_OF_ATOMS
#include "test_number_of_atoms.h"
#endif

using namespace std;

static size_t basename_start_calc (const char *filename) {
    const char *base = strrchr (filename, '/');
    return base ? (base - filename + 1) : 0;
}

size_t basename_start (const char *filename) {
    static size_t retval = basename_start_calc (filename);
    return retval;
}

//#define STR_(t) #t
//#define STR(t) STR_(t)
#define BASENAME() ((__FILE__ ":") + basename_start (__FILE__))

int init_by_foo3 (void) {
    cout << __FUNCTION__ << "() line " << __LINE__ << endl;
    return 3;
}

int init_by_foo4 (void) {
    cout << __FUNCTION__ << "() line " << __LINE__ << endl;
    return 4;
}

int a_val3 = init_by_foo3 ();
int a_val4 = init_by_foo4 ();

bool u_tests (void) {
    cout << __FUNCTION__ << endl;
#ifdef ALGORITHMS_OOP
    EXPECT_TRUE (test_findDuplicate ());
    EXPECT_TRUE (test_singleNumber ());
#endif
#ifdef NUMBER_OF_ATOMS
    EXPECT_TRUE (test_number_of_atoms ());
#endif

#ifdef BRICK_WALL
    EXPECT_TRUE (test_brick_wall ());
#endif

#ifdef INTERVALS
    EXPECT_TRUE (test_remove_Covered_Intervals ());
#endif
    cout << "u_tests fine" << endl;
    return true;
}