#ifndef VECTOR_CALC_H
#define VECTOR_CALC_H

#include <stdbool.h>
#include <stdint.h>

#define M_PI 3.1415f
//#define DEBUG_VECTOR_CALC

typedef struct xDot_t {
    double x;
    double y;
    double z;
} Dot_t;

typedef struct xVector_t {
    double dx;
    double dy;
    double dz;
} Vector_t;

typedef struct xLine_t {
    Vector_t vector;
    Dot_t start;
} Line_t;

bool is_line_segment_crossed (Line_t line_a, Line_t line_b);
double calc_angle_between_vectors (Vector_t *v1, Vector_t *v2);
Vector_t init_vector (double dx, double dy, double dz);
Dot_t init_dot (double x, double y, double z);
char *compose_2d_line_equation (Dot_t p1, Dot_t p2);

void print_dot (Dot_t d, char *text);
void print_vector (Vector_t v, char *text);

#endif /*VECTOR_CALC_H*/
