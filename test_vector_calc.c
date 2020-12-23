#include "test_vector_calc.h"

#include "uTests.h"
#include "vector_calc.h"

bool test_angle_between_vectors (void) {
    printf ("\n%s()", __FUNCTION__);
    double angle_rad;
    Vector_t vector_a = init_vector (0.0f, 3.0f, 0.0f);
    Vector_t vector_b = init_vector (3.0f, 0.0f, 0.0f);
    angle_rad = calcAngleBetweenVectors (&vector_a, &vector_b);
    EXPECT_TRUE (is_double_equal_absolute (angle_rad, M_PI / 2, 0.1));

    angle_rad = calcAngleBetweenVectors (&vector_b, &vector_a);
    EXPECT_TRUE (is_double_equal_absolute (angle_rad, -M_PI / 2, 0.1));

    return true;
}

bool test_vector_calc (void) {
    printf ("\n%s()", __FUNCTION__);

    EXPECT_TRUE (test_angle_between_vectors ());

    Line_t line_a;
    Line_t line_b;

    line_a.start = init_dot (0.0f, 0.0f, 0.0f);
    line_a.vector = init_vector (3.0f, 0.0f, 0.0f);

    line_b.start = init_dot (1.0f, -1.0f, 0.0);
    line_b.vector = init_vector (0.0f, 3.0f, 0.0);

    EXPECT_TRUE (is_line_segment_crossed (line_a, line_b));

    line_a.start = init_dot (0.0f, 0.0f, 0.0);
    line_a.vector = init_vector (3.0f, 0.0f, 0.0);

    line_b.start = init_dot (1.0f, 1.0f, 0.0);
    line_b.vector = init_vector (0.0f, 3.0f, 0.0);

    EXPECT_FALSE (is_line_segment_crossed (line_a, line_b));

    return true;
}
