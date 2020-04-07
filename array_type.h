#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct xArray_t {
    int arrSize;
    int *pArr;
} Array_t;

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_TYPE_H */
