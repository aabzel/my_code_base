#include "rx_algorithm.h"

static int32_t rx_lower_bound_kv (int16_t kv_key, const lookup_table_rec16_t kv_base [], uint32_t kv_count);

int32_t lower_bound_u32 (uint32_t key_u32, const uint32_t base_u32 [], uint32_t count_u32) {
    int32_t imin_u32 = 0;
    uint32_t _count_u32 = count_u32;
    while (_count_u32 > 0U) {
        uint32_t half_u32 = _count_u32 >> 1U;
        int32_t imid_u32 = imin_u32 + (int32_t)half_u32;
        if (base_u32 [imid_u32] < key_u32) {
            imin_u32 = imid_u32 + 1;
            _count_u32 -= half_u32 + 1U;
        } else {
            _count_u32 = half_u32;
        }
    }
    if ((imin_u32 >= (int32_t) count_u32) || (base_u32 [imin_u32] != key_u32)) {
        imin_u32 = -imin_u32 - 1;
    }
    return imin_u32;
}

static int32_t rx_lower_bound_kv (int16_t kv_key, const lookup_table_rec16_t kv_base [], uint32_t kv_count) {
    int32_t imin = 0;
    uint32_t _count = kv_count;
    while (_count > 0U) {
        uint32_t half = _count >> 1U;
        int32_t imid = imin + (int32_t) half;
        const int32_t compare_result = (int32_t)kv_base [imid].rec_key - kv_key;
        if (compare_result < 0) {
            imin = imid + 1;
            _count -= half + 1U;
        } else {
            _count = half;
        }
    }
    if ((imin >= (int32_t) kv_count) || (kv_base [imin].rec_key != kv_key)) {
        imin = -imin - 1;
    }
    return imin;
}

int32_t lookup_table16 (int16_t key, const lookup_table_rec16_t base [], uint32_t count) {
    int32_t result;
    int32_t index = rx_lower_bound_kv (key, base, count);
    if (index >= 0) {
        result = base [index].rec_value;
    } else {
        index = -index - 1;
        if (index == (int32_t) count) {
            result = base [count - 1U].rec_value;
        } else {
            if (index == 0) {
                result = base [0].rec_value;
            } else {
                int16_t x1 = base [index - 1].rec_key;
                int16_t x2 = base [index].rec_key;
                int16_t y1 = base [index - 1].rec_value;
                int16_t y2 = base [index].rec_value;
                int32_t k = (((int32_t)y2 - y1) * (int32_t) 100) / ((int32_t)x2 - x1);
                result = y1 + ((((int32_t)key - x1) * k) / 100);
            }
        }
    }
    return result;
}
