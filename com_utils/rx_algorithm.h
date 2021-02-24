#ifndef RX_ALGORITHM_H
#define RX_ALGORITHM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int16_t rec_key;
    int16_t rec_value;
} lookup_table_rec16_t;

/* Find element in sorted uint32_t array */
int32_t lower_bound_u32 (uint32_t key_u32, const uint32_t base_u32[], uint32_t count_u32);
int32_t lookup_table16 (int16_t key, const lookup_table_rec16_t base[], uint32_t count);

#ifdef __cplusplus
}
#endif

#endif /* RX_ALGORITHM_H */
