#include "rx_utils.h"

uint8_t rx_max8u (uint8_t max8u_x1, uint8_t max8u_x2) { return (((max8u_x1) > (max8u_x2)) ? (max8u_x1) : (max8u_x2)); }

uint8_t rx_min8u (uint8_t min8u_x1, uint8_t min8u_x2) { return (((min8u_x1) < (min8u_x2)) ? (min8u_x1) : (min8u_x2)); }

uint16_t rx_max16u (uint16_t max16u_x1, uint16_t max16u_x2) {
    return (((max16u_x1) > (max16u_x2)) ? (max16u_x1) : (max16u_x2));
}

uint16_t rx_min16u (uint16_t min16u_x1, uint16_t min16u_x2) {
    return (((min16u_x1) < (min16u_x2)) ? (min16u_x1) : (min16u_x2));
}

uint32_t rx_max32u (uint32_t max32u_x1, uint32_t max32u_x2) {
    return (((max32u_x1) > (max32u_x2)) ? (max32u_x1) : (max32u_x2));
}

uint32_t rx_min32u (uint32_t min32u_x1, uint32_t min32u_x2) {
    return (((min32u_x1) < (min32u_x2)) ? (min32u_x1) : (min32u_x2));
}

int8_t rx_max8 (int8_t max8_x1, int8_t max8_x2) { return (((max8_x1) > (max8_x2)) ? (max8_x1) : (max8_x2)); }

int8_t rx_min8 (int8_t min8_x1, int8_t min8_x2) { return (((min8_x1) < (min8_x2)) ? (min8_x1) : (min8_x2)); }

int16_t rx_max16 (int16_t max16_x1, int16_t max16_x2) { return (((max16_x1) > (max16_x2)) ? (max16_x1) : (max16_x2)); }

int16_t rx_min16 (int16_t min16_x1, int16_t min16_x2) { return (((min16_x1) < (min16_x2)) ? (min16_x1) : (min16_x2)); }

int32_t rx_max32 (int32_t max32_x1, int32_t max32_x2) { return (((max32_x1) > (max32_x2)) ? (max32_x1) : (max32_x2)); }

int32_t rx_min32 (int32_t min32_x1, int32_t min32_x2) { return (((min32_x1) < (min32_x2)) ? (min32_x1) : (min32_x2)); }

uint32_t swap32 (uint32_t u32_num) {
    return ((((u32_num) >> 24) & 0xffU) | (((u32_num) << 8) & 0xff0000U) | (((u32_num) >> 8) & 0xff00U) |
            (((u32_num) << 24) & 0xff000000U));
}

uint16_t swap16 (uint16_t u16_num) {
    return (((uint16_t) ((u16_num) >> 8) & 0xffU) | ((uint16_t) ((u16_num) << 8) & 0xff00U));
}

#define TEN_SPACES "          "
const char *get_spaces_str (uint32_t spaces_length) {
    static char szSpaces[101] =
        TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES;
    uint32_t last_index = sizeof (szSpaces) - 1U;
    if (spaces_length > last_index) {
        last_index = 0U;
    } else {
        last_index -= spaces_length;
    }
    return &szSpaces[last_index];
}
