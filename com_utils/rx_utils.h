#ifndef UTILS_RX_UTILS_H_
#define UTILS_RX_UTILS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ghs__)
/* MISRA 2004 Rule 19.7: function-like macro not allowed -- use function instead */
#pragma ghs nowarning 1862
/* MISRA 2004 Rule 19.4: macro definition can only be used for a braced initializer, constant, parenthesized expression,
 * type qualifier, storage class  */
#pragma ghs nowarning 1859
/* MISRA 2004 Rule 19.10: parameter of function-like macro must be enclosed in parentheses */
#pragma ghs nowarning 1829
/* MISRA 2004 Rule 19.13: # or ## operator not allowed */
#pragma ghs nowarning 1830
#endif

#define RX_ARRAY_SIZE(x) (sizeof (x) / sizeof ((x)[0]))

#ifdef __GNUC__
#define RX_DATA_SECTION_ATTR(name) __attribute__ ((section (name)))
#ifndef INLINE
#define INLINE inline
#endif
#ifdef SPC58
#define NOINIT
#else /* SPC58 */
#define NOINIT __attribute__ ((section (".noinit")))
#endif /* SPC58 */
#endif /* __GNUC__ */

#ifdef __ghs__
#define RX_DATA_SECTION_ATTR(name) __attribute__ ((section (name)))
#define NOINIT
#ifndef INLINE
#define INLINE inline
#endif
#endif /* __ghs__ */

/* Compile time assert */
/* Note we need the 2 concats below because arguments to ##
 * are not expanded, so we need to expand __LINE__ with one indirection
 * before doing the actual concatenation. */
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_ (a, b)
#define ct_assert(e)                                                                                                   \
    {                                                                                                                  \
        enum { ASSERT_CONCAT (assert_line_, __LINE__) = 1 / (!!(e)) };                                                 \
    }

#if defined(__ghs__)
#pragma ghs endnowarning 1830
#pragma ghs endnowarning 1829
#pragma ghs endnowarning 1859
#pragma ghs endnowarning 1862
#endif

uint8_t rx_max8u (uint8_t max8u_x1, uint8_t max8u_x2);
uint8_t rx_min8u (uint8_t min8u_x1, uint8_t min8u_x2);
uint16_t rx_max16u (uint16_t max16u_x1, uint16_t max16u_x2);
uint16_t rx_min16u (uint16_t min16u_x1, uint16_t min16u_x2);
uint32_t rx_max32u (uint32_t max32u_x1, uint32_t max32u_x2);
uint32_t rx_min32u (uint32_t min32u_x1, uint32_t min32u_x2);
int8_t rx_max8 (int8_t max8_x1, int8_t max8_x2);
int8_t rx_min8 (int8_t min8_x1, int8_t min8_x2);
int16_t rx_max16 (int16_t max16_x1, int16_t max16_x2);
int16_t rx_min16 (int16_t min16_x1, int16_t min16_x2);
int32_t rx_max32 (int32_t max32_x1, int32_t max32_x2);
int32_t rx_min32 (int32_t min32_x1, int32_t min32_x2);
uint32_t swap32 (uint32_t u32_num);
uint16_t swap16 (uint16_t u16_num);
const char *get_spaces_str (uint32_t spaces_length);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_RX_UTILS_H_ */
