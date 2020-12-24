#include "test_vector_calc.h"

#include "uTests.h"
#include "vector_calc.h"

static bool test_line_equation (void) {
    Dot_t p0 = init_dot (0.0f, 0.0f, 0.0f);
    Dot_t p45 = init_dot (10.0f, 10.0f, 0.0f);
    Dot_t px1 = init_dot (4.0f, 0.0f, 0.0f);
    Dot_t px2 = init_dot (4.0f, 6.0f, 0.0f);

    Dot_t py1 = init_dot (42.0f, -6.0f, 0.0f);
    Dot_t py2 = init_dot (4.0f, -6.0f, 0.0f);

    EXPECT_EQ_STR ("   0.10*x+  -0.10*y=   0.00", compose_2d_line_equation (p0, p45));
    EXPECT_EQ_STR ("x=   4.00", compose_2d_line_equation (px1, px2));
    EXPECT_EQ_STR ("y=  -6.00", compose_2d_line_equation (py1, py2));
    EXPECT_EQ_STR ("same", compose_2d_line_equation (px1, px1));
    EXPECT_EQ_STR ("   0.03*x+   0.17*y=   0.11", compose_2d_line_equation (px1, py1));
    return true;
}

static bool test_angle_between_vectors (void) {
    printf ("\n%s()", __FUNCTION__);
    double angle_rad;
    Vector_t vector_a = init_vector (3.0f, 0.0f, 0.0f);
    Vector_t vector_b = init_vector (0.0f, 3.0f, 0.0f);
    angle_rad = calc_angle_between_vectors (&vector_a, &vector_b);
    printf ("\n%s() angle %f", __FUNCTION__, angle_rad);
    EXPECT_TRUE (is_double_equal_absolute (angle_rad, M_PI / 2, 0.02));

    angle_rad = calc_angle_between_vectors (&vector_b, &vector_a);
    EXPECT_TRUE (is_double_equal_absolute (angle_rad, -M_PI / 2, 0.01));

    return true;
}

bool test_vector_calc (void) {
    printf ("\n%s()", __FUNCTION__);
    EXPECT_TRUE (test_line_equation ());
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
