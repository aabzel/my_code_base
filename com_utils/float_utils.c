#include "float_utils.h"

bool is_floats_equal (float_t valA, float_t valB) { return is_float_equal_relative (valA, valB, (float_t)F_EPSILON); }

/*
 *
 */
bool is_float_equal_relative (float_t a__fife, float_t b__fife, float_t relative_epsilon__fife) {
    bool retval__fife;
    if (fabsf (a__fife - b__fife) <=
        fmaxf (fabsf (relative_epsilon__fife * b__fife), fabsf (relative_epsilon__fife * a__fife))) {
        retval__fife = true;
    } else {
        retval__fife = false;
    }
    return retval__fife;
}

/*
 *
 */
bool is_double_equal_relative (double_t a__fide, double_t b__fide, double_t relative_epsilon__fide) {
    bool retval__fide;
    if (fabs (a__fide - b__fide) <=
        fmax (fabs (relative_epsilon__fide * b__fide), fabs (relative_epsilon__fide * a__fide))) {
        retval__fide = true;
    } else {
        retval__fide = false;
    }
    return retval__fide;
}

bool is_float_equal_absolute (float_t a__fife, float_t b__fife, float_t absolute_epsilon__fife) {
    bool retval__fife;
    if (fabsf (a__fife - b__fife) <= absolute_epsilon__fife) {
        retval__fife = true;
    } else {
        retval__fife = false;
    }
    return retval__fife;
}

bool is_double_equal_absolute (double_t a__fide, double_t b__fide, double_t absolute_epsilon__fide) {
    bool retval__fide;
    if (fabs (a__fide - b__fide) <= absolute_epsilon__fide) {
        retval__fide = true;
    } else {
        retval__fide = false;
    }
    return retval__fide;
}

float_t float_max (float_t x1, float_t x2) {
    float_t out_val = x1;
    if (x1 < x2) {
        out_val = x2;
    }
    return out_val;
}

float_t float_limiter (float_t in_value, float_t up_limit) {
    float_t out_value = in_value;
    if (up_limit < in_value) {
        out_value = up_limit;
    }
    return out_value;
}

float_t float_limiter_down_up (float_t in_value, float_t down_limit, float_t up_limit) {
    float_t out_value = in_value;
    if (up_limit < in_value) {
        out_value = up_limit;
    }
    if (in_value < down_limit) {
        out_value = down_limit;
    }
    return out_value;
}
