#include "vector_calc.h"

#include <string.h>

#include "float_utils.h"

double norm (Vector_t *v) {
    //Евклидова норма:
    double norm;
    norm = sqrt ((v->dx) * (v->dx) + (v->dy) * (v->dy) + (v->dz) * (v->dz));
    return norm;
}

double dot_product (Vector_t *v1, Vector_t *v2) {
    double dot = 0.0;
    dot = (v1->dx) * (v2->dx) + (v1->dy) * (v2->dy) + (v1->dz) * (v2->dz);
    return dot;
}

Vector_t init_vector (double dx, double dy, double dz) {
    Vector_t vec_out;
    vec_out.dx = dx;
    vec_out.dy = dy;
    vec_out.dz = dz;
    return vec_out;
}

Dot_t init_dot (double x, double y, double z) {
    Dot_t dot_out;
    dot_out.x = x;
    dot_out.y = y;
    dot_out.z = z;
    return dot_out;
}

Vector_t cross (Vector_t *a, Vector_t *b) {
    Vector_t v;
    v.dx = a->dy * b->dz - a->dz * b->dy;
    v.dy = -(a->dx * b->dz - a->dz * b->dx);
    v.dz = a->dx * b->dy - a->dy * b->dx;
    return v;
}

double mySign (double val) {
    if (0.0 < val) {
        return 1.0;
    }
    if (val < 0.0) {
        return -1.0;
    }
    return 0.0;
}

double calc_angle_between_vectors (Vector_t *v1, Vector_t *v2) {
#ifdef DEBUG_VECTOR_CALC
    printf ("\n%s()", __FUNCTION__);
#endif
    //  betta rad  0.....3.14159
#ifdef DEBUG_VECTOR_CALC
    print_vector (*v1, "V1");
    print_vector (*v2, "V2");
#endif
    double betta = 0.0, norm1, norm2, absBetta;
    double dotPr;
    Vector_t v3;
    norm1 = norm (v1);
    norm2 = norm (v2);
    if (0.0 == norm1 || 0.0 == norm2) {
        return 0.0;
    } else {
        dotPr = dot_product (v1, v2);
        absBetta = acos (dotPr / (norm1 * norm2));
        // scalar multiplication gives just module of  the angle.
        // vector multiplication gives the sign of the angle.
        v3 = cross (v1, v2);
        if ((0.0 == v3.dx) && (0.0 == v3.dy) && (0.0 == v3.dz)) {
            betta = absBetta;
        } else {
            betta = mySign (v3.dz) * absBetta;
        }
        return betta;
    }
}

struct hand {
    float angleDeg;
    float x;
    float y;
};

float deg2radians (float degrees) {
    const float pi_on_180 = 4.0 * atan (1.0) / 180.0;
    return degrees * pi_on_180;
}

float radians2deg (float radians) { return radians * (180.0 / M_PI); }

float calc_angle_min (int min) {
    // step for minute hand is 6 deg
    float angle = 0.0;
    angle = 90.0 - 6.0 * min;
    return angle;
}

float calc_angle_hour (int hour, int min) {
    // Step of the hour hand in minute is = 0.5 deg
    float angle;
    angle = (90.0 - hour * 30) - 0.5 * min;
    return angle;
}

void init_hand (struct hand *hand) {
    hand->x = cos (deg2radians (hand->angleDeg));
    hand->y = sin (deg2radians (hand->angleDeg));
}

float dot (struct hand *sHour, struct hand *sMin) {
    float dot_product = 0.0;
    dot_product = (sHour->x) * (sMin->x) + (sHour->y) * (sMin->y);
    return dot_product;
}

float calc_angle_between_clock_hands (int hour24, int min) {
    float absAngleRad = 0.0;
    float dotPruduct = 0.0;
    struct hand vHour, vMin;

    vHour.angleDeg = calc_angle_hour (hour24, min);
    vMin.angleDeg = calc_angle_min (min);

    init_hand (&vHour);
    init_hand (&vMin);

    dotPruduct = dot (&vHour, &vMin);
    absAngleRad = acos (dotPruduct);
    return radians2deg (absAngleRad);
}

Dot_t get_line_start (Line_t line_a) { return line_a.start; }

Dot_t get_line_end (Line_t in_line) {
    Dot_t end_point;
    end_point.x = in_line.start.x + in_line.vector.dx;
    end_point.y = in_line.start.y + in_line.vector.dy;
    end_point.z = in_line.start.z + in_line.vector.dz;
    return end_point;
}

Vector_t compose_vector_from_2dot (Dot_t da, Dot_t db) {
    Vector_t out_vec;
    out_vec.dx = db.x - da.x;
    out_vec.dy = db.y - da.y;
    out_vec.dz = db.z - da.z;
    return out_vec;
}

bool is_signe_different (double a, double b) {
    if ((a < 0) && (0 < b)) {
        return true;
    }
    if ((b < 0) && (0 < a)) {
        return true;
    }
    return false;
}

bool is_line_segment_crossed (Line_t line_a, Line_t line_b) {
    bool res = false;
#ifdef DEBUG_VECTOR_CALC
    printf ("\n%s()", __FUNCTION__);
#endif
    Dot_t a_start = get_line_start (line_a);
    Dot_t b_start = get_line_start (line_b);
    Dot_t a_end = get_line_end (line_a);
    Dot_t b_end = get_line_end (line_b);
#ifdef DEBUG_VECTOR_CALC
    print_dot (a_start, "a_start");
    print_dot (a_end, "a_end");
    print_dot (b_start, "b_start");
    print_dot (b_end, "b_end");
#endif

    Vector_t a_st_b_st = compose_vector_from_2dot (a_start, b_start);
    Vector_t a_st_b_en = compose_vector_from_2dot (a_start, b_end);
    Vector_t b_st_a_st = compose_vector_from_2dot (b_start, a_start);
    Vector_t b_st_a_en = compose_vector_from_2dot (b_start, a_end);
#ifdef DEBUG_VECTOR_CALC
    print_vector (a_st_b_en, "a_st_b_en");
    print_vector (a_st_b_st, "a_st_b_st");
    print_vector (b_st_a_st, "b_st_a_st");
    print_vector (b_st_a_en, "b_st_a_en");
#endif

    double a_deg_left = calc_angle_between_vectors (&line_a.vector, &a_st_b_st);
    double a_deg_right = calc_angle_between_vectors (&line_a.vector, &a_st_b_en);
    double b_deg_left = calc_angle_between_vectors (&line_b.vector, &b_st_a_st);
    double b_deg_right = calc_angle_between_vectors (&line_b.vector, &b_st_a_en);
#ifdef DEBUG_VECTOR_CALC
    printf ("\n deg %f", a_deg_left);
    printf ("\n deg %f", a_deg_right);
    printf ("\n deg %f", b_deg_left);
    printf ("\n deg %f", b_deg_right);
#endif

    if (is_signe_different (a_deg_left, a_deg_right) && is_signe_different (b_deg_left, b_deg_right)) {
        res = true;
    }

    /*A x + B y + C = 0*/
    return res;
}

char *compose_2d_line_equation (Dot_t p1, Dot_t p2, float *out_equation) {
    float a = 0.0f, b = 0.0f, c = 0.0f;
    printf ("\n%s()", __FUNCTION__);
    static char out_str[100] = "";
    out_equation[0] = 0.0f;
    out_equation[1] = 0.0f;
    out_equation[2] = 0.0f;
    bool done = false;
    bool x_same = is_double_equal_absolute (p2.x, p1.x, 0.01);
    if (false == x_same) {
        a = (1 / (p2.x - p1.x));
    } else {
        done = true;
        out_equation[0] = 1;
        out_equation[2] = p1.x;
        snprintf (out_str, sizeof (out_str), "x=%7.2f", p1.x);
    }
    bool y_same = is_double_equal_absolute (p2.y, p1.y, 0.01);
    if (false == y_same) {
        b = -(1 / (p2.y - p1.y));
    } else {
        done = true;
        out_equation[1] = 1;
        out_equation[2] = p1.y;
        snprintf (out_str, sizeof (out_str), "y=%7.2f", p1.y);
    }
    if ((false == x_same) && (false == y_same)) {
        c = (p1.x / (p2.x - p1.x)) - (p1.y / (p2.x - p1.y));
    } else {
        done = true;
        if ((true == x_same) && (true == y_same)) {
            snprintf (out_str, sizeof (out_str), "same");
        }
    }

    if (false == done) {
        snprintf (out_str, sizeof (out_str), "%7.2f*x+%7.2f*y=%7.2f", a, b, c);
        out_equation[0] = a;
        out_equation[1] = b;
        out_equation[2] = c;
    }
    return out_str;
}

float calc_determinant_2x2 (float *arr) {
    float det = 0;
    float a = arr[0];
    float b = arr[1];
    float c = arr[2];
    float d = arr[3];
    det = a * d - b * c;
    return det;
}

void print_2d_system (float *a, float *b) {
    printf ("\n%fx + %fy =%f", a[0], a[1], b[0]);
    printf ("\n%fx + %fy =%f\n", a[2], a[3], b[1]);
}

bool solve_2d_equation (float *a, float *b, float *x_out) {
    float determinamt = calc_determinant_2x2 (a);
    float determinamt_x = 0;
    float determinamt_y = 0;
    print_2d_system (a, b);
    bool res = false;
    float *a_temp = (float *)malloc (4 * sizeof (float));
    if (a_temp) {
        memcpy (a_temp, a, 4 * sizeof (float));
        a_temp[0] = b[0];
        a_temp[2] = b[1];
        determinamt_x = calc_determinant_2x2 (a_temp);
        printf ("\n[d] determinamt_x %f", determinamt_x);
        memcpy (a_temp, a, 4 * sizeof (float));
        a_temp[1] = b[0];
        a_temp[3] = b[1];
        determinamt_y = calc_determinant_2x2 (a_temp);
        printf ("\n[d] determinamt_y %f", determinamt_y);
        if (false == is_float_equal_absolute (0.0, determinamt, 0.001)) {
            printf ("\n[d] determinamt %f", determinamt);
            x_out[0] = determinamt_x / determinamt;
            x_out[1] = determinamt_y / determinamt;
            res = true;
        } else {
            printf ("\n[!] determinamt zero");
        }
        free (a_temp);
    }
    return res;
}

#ifdef DEBUG_VECTOR_CALC
void print_vector (Vector_t v, char *text) { printf ("\n %s V(%f, %f, %f)", text, v.dx, v.dy, v.dz); }
void print_dot (Dot_t d, char *text) { printf ("\n %s D[%f, %f, %f]", text, d.x, d.y, d.z); }
#endif

//Даны 2 точки построить уравнение прямой
