#ifndef __ARRAY_TYPE_H
#define __ARRAY_TYPE_H

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

#endif /* __ARRAY_TYPE_H */
