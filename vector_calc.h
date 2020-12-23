#ifndef VECTOR_CALC_H
#define VECTOR_CALC_H

#include <stdbool.h>
#include <stdint.h>

#define M_PI 3.1415f

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
double calcAngleBetweenVectors (Vector_t *v1, Vector_t *v2);
Vector_t init_vector (double dx, double dy, double dz);
Dot_t init_dot (double x, double y, double z);

void print_dot (Dot_t d);
void print_vector (Vector_t v);

#endif /*VECTOR_CALC_H*/
