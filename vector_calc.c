#include "vector_calc.h"

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

double calcAngleBetweenVectors (Vector_t *v1, Vector_t *v2) {
    printf ("\n%s()", __FUNCTION__);
    //  betta rad  0.....3.14159
    print_vector (*v1);
    print_vector (*v2);
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
    Dot_t a_start = get_line_start (line_a);
    Dot_t b_start = get_line_start (line_b);
    Dot_t a_end = get_line_end (line_a);
    Dot_t b_end = get_line_end (line_b);

    printf ("\n a_start\n");
    print_dot (a_start);
    printf ("\n a_end\n");
    print_dot (a_end);
    printf ("\n b_start\n");
    print_dot (b_start);
    printf ("\n b_end\n");
    print_dot (b_end);

    printf ("\n Dirrections\n");
    Vector_t a_st_b_st = compose_vector_from_2dot (a_start, b_start);
    print_vector (a_st_b_st);
    Vector_t a_st_b_en = compose_vector_from_2dot (a_start, b_end);
    print_vector (a_st_b_en);
    Vector_t b_st_a_st = compose_vector_from_2dot (b_start, a_start);
    print_vector (b_st_a_st);
    Vector_t b_st_a_en = compose_vector_from_2dot (b_start, a_end);
    print_vector (b_st_a_en);

    double a_deg_left = calcAngleBetweenVectors (&line_a.vector, &a_st_b_st);
    printf ("\n deg %f", a_deg_left);
    double a_deg_right = calcAngleBetweenVectors (&line_a.vector, &a_st_b_en);
    printf ("\n deg %f", a_deg_right);
    double b_deg_left = calcAngleBetweenVectors (&line_b.vector, &b_st_a_st);
    printf ("\n deg %f", b_deg_left);
    double b_deg_right = calcAngleBetweenVectors (&line_b.vector, &b_st_a_en);
    printf ("\n deg %f", b_deg_right);

    if (is_signe_different (a_deg_left, a_deg_right) && is_signe_different (b_deg_left, b_deg_right)) {
        res = true;
    }

    /*A x + B y + C = 0*/
    return res;
}

void print_vector (Vector_t v) { printf ("\n V(%f, %f, %f)", v.dx, v.dy, v.dz); }

void print_dot (Dot_t d) { printf ("\n D[%f, %f, %f]", d.x, d.y, d.z); }

//Даны 2 точки построить уравнение прямой
