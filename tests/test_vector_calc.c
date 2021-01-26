#include "test_vector_calc.h"

#include "float_utils.h"
#include "uTests.h"
#include "vector_calc.h"

static bool test_line_equation (void) {
    Dot_t p0 = init_dot (0.0f, 0.0f, 0.0f);
    Dot_t p45 = init_dot (10.0f, 10.0f, 0.0f);
    Dot_t px1 = init_dot (4.0f, 0.0f, 0.0f);
    Dot_t px2 = init_dot (4.0f, 6.0f, 0.0f);

    Dot_t py1 = init_dot (42.0f, -6.0f, 0.0f);
    Dot_t py2 = init_dot (4.0f, -6.0f, 0.0f);
    float equation[3];
    EXPECT_EQ_STR ("   0.10*x+  -0.10*y=   0.00", compose_2d_line_equation (p0, p45, equation));
    EXPECT_EQ_STR ("x=   4.00", compose_2d_line_equation (px1, px2, equation));
    EXPECT_EQ_STR ("y=  -6.00", compose_2d_line_equation (py1, py2, equation));
    EXPECT_EQ_STR ("same", compose_2d_line_equation (px1, px1, equation));
    EXPECT_EQ_STR ("   0.03*x+   0.17*y=   0.11", compose_2d_line_equation (px1, py1, equation));
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

static bool test_sle_solver (void) {
    float ratio[4];
    float b[4];

    float equation1[3];
    float equation2[3];

    Line_t line_a;
    line_a.start = init_dot (0.0f, 0.0f, 0.0f);
    line_a.vector = init_vector (3.0f, 0.0f, 0.0f);

    Line_t line_b;
    line_b.start = init_dot (1.0f, -1.0f, 0.0);
    line_b.vector = init_vector (0.0f, 3.0f, 0.0);

    get_line_end (line_a);
    get_line_end (line_b);
    printf ("\n Eq1 %s", compose_2d_line_equation (line_a.start, get_line_end (line_a), equation1));
    printf ("\n Eq2 %s", compose_2d_line_equation (line_b.start, get_line_end (line_b), equation2));
    ratio[0] = equation1[0];
    ratio[1] = equation1[1];
    ratio[2] = equation2[0];
    ratio[3] = equation2[1];
    b[0] = equation1[2];
    b[1] = equation2[2];
    float x_out[2] = {0, 0};
    bool res = solve_2d_equation (ratio, b, x_out);
    EXPECT_TRUE (res);
    if (true == res) {
        printf ("\n x:%f y:%f", x_out[0], x_out[1]);
    }
    return true;
}

bool test_vector_calc (void) {
    printf ("\n%s()", __FUNCTION__);
    EXPECT_TRUE (test_sle_solver ());
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
