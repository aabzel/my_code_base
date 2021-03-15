#ifndef UNIT_TEST_CHECK_H_
#define UNIT_TEST_CHECK_H_

#include <string.h>
#include <math.h>

#include "io_utils.h"
#include "print_buffer.h"
#include "timer_utils.h"
#include "unit_test_run.h"

#ifdef  __cplusplus

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef __ghs__
#   define LOCATION __BASE__ ":" TOSTRING(__LINE__)
#else
#   define LOCATION __FILE__ ":" TOSTRING(__LINE__)
#endif

void test_near (
    const double_t x,
    const double_t y,
    const double_t error,
    const char *expected,
    const char *actual,
    const char *error_,
    const char *location);
void test_eq (const double_t x, const double_t y, const char *expected, const char *actual, const char *location);
void test_eq (const float_t x, const float_t y, const char *expected, const char *actual, const char *location);

void ut_dump_value (uint8_t v);
void ut_dump_value (uint16_t v);
void ut_dump_value (uint32_t v);
void ut_dump_value (uint64_t v);
void ut_dump_value (int8_t v);
void ut_dump_value (int16_t v);
void ut_dump_value (int32_t v);
void ut_dump_value (int64_t v);
void ut_dump_value (float_t v);
void ut_dump_value (double_t v);
void ut_dump_value (const void *v);
void ut_dump_value (bool v);
void ut_dump_value (unsigned int v);
void ut_dump_value (unsigned long v);
void ut_dump_value (int v);

#define TEST_CHECK(name,op) \
template<typename T1, typename T2> \
static void test_##name(T1 x, T2 y, \
                const char * x_name, \
                const char * y_name, \
                const char * location) \
{ \
    if(!(x op y)) { \
        uint32_t now = get_time_ms32 (); \
        test_failed = true; \
        io_flush(); \
        print_buf_stream_en = false; \
        io_printf("%u.%03u TEST(%s %s %s ) FAILED at %s" CRLF, now / 1000U, now % 1000U, x_name, #op, y_name, location); \
        io_printf("| %s = ", x_name); \
        ut_dump_value(x); \
        io_puts(CRLF); \
        io_printf("| %s = ", y_name); \
        ut_dump_value(y); \
        io_puts(CRLF); \
        io_flush(); \
        print_buf_stream_en = true; \
    } \
}

#define TEST_STR_CHECK(name,op) \
template<typename T1, typename T2> \
void test_##name(const T1 x, const T2 y, \
                const char * x_name, \
                const char * y_name, \
                const char * location) \
{ \
    if(!(0 op strcmp(x,y))) { \
        uint32_t now = get_time_ms32 (); \
        test_failed = true; \
        io_flush(); \
        print_buf_stream_en = false; \
        io_printf("%u.%03u TEST(%s %s %s) FAILED at %s" CRLF, now / 1000U, now % 1000U, x_name, #op, y_name, location); \
        io_printf("| %s = \"%s\" len=%d" CRLF, x_name, x, strlen(x)); \
        io_printf("| %s = \"%s\" len=%d" CRLF, y_name, y, strlen(y)); \
        io_flush(); \
        print_buf_stream_en = true; \
    } \
}

TEST_CHECK(eq, ==)
TEST_CHECK(ne, !=)
TEST_CHECK(lt, <)
TEST_CHECK(le, <=)
TEST_CHECK(gt, >)
TEST_CHECK(ge, >=)

TEST_STR_CHECK(str_eq, ==)
TEST_STR_CHECK(str_ne, !=)

#define EMBED_TEST_STR_NEQ(expected, actual) test_str_ne((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_STR_EQ(expected, actual) test_str_eq((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_NE(expected, actual) test_ne((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_EQ(expected, actual) test_eq((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_LT(expected, actual) test_lt((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_LE(expected, actual) test_le((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_GT(expected, actual) test_gt((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_GE(expected, actual) test_ge((expected), (actual), #expected, #actual, LOCATION)

#define EMBED_TEST_NEAR(expected, actual, abs_error) test_near((expected), (actual), (abs_error), #expected, #actual, #abs_error, LOCATION)

#define ASSERT_RETURN() \
    if(test_failed) {return;}

#define ASSERT_TRUE(condition) \
    EMBED_TEST_EQ( true, (condition)); \
    ASSERT_RETURN()

#define ASSERT_FALSE(condition) \
    EMBED_TEST_EQ( false, (condition)); \
    ASSERT_RETURN()

/* val1 == val2 */
#define ASSERT_EQ(val1, val2) \
    EMBED_TEST_EQ( (val1), (val2)); \
    ASSERT_RETURN()

/* val1 != val2 */
#define ASSERT_NE(val1, val2) \
    EMBED_TEST_NE( (val1), (val2)); \
    ASSERT_RETURN()

/* val1 < val2 */
#define ASSERT_LT(val1, val2) \
    EMBED_TEST_LT( (val1), (val2)); \
    ASSERT_RETURN()

/* val1 <= val2 */
#define ASSERT_LE(val1, val2) \
    EMBED_TEST_LE( (val1), (val2)); \
    ASSERT_RETURN()

/* val1 > val2 */
#define ASSERT_GT(val1, val2) \
    EMBED_TEST_GT( (val1), (val2)); \
    ASSERT_RETURN()

/* val1 >= val2*/
#define ASSERT_GE(val1, val2) \
    EMBED_TEST_GE( (val1), (val2)); \
    ASSERT_RETURN()

#define ASSERT_STREQ(expected_str, actual_str) \
    EMBED_TEST_STR_EQ( (expected_str), (actual_str)); \
    ASSERT_RETURN()

#define ASSERT_STRNE(expected_str, actual_str) \
    EMBED_TEST_STR_NEQ( (expected_str), (actual_str)); \
    ASSERT_RETURN()

#define ASSERT_FLOAT_EQ(val1, val2) \
    EMBED_TEST_EQ( (val1), (val2)); \
    ASSERT_RETURN()

#define ASSERT_DOUBLE_EQ(val1, val2) \
    EMBED_TEST_EQ( (val1), (val2)); \
    ASSERT_RETURN()

#define EXPECT_TRUE(condition) \
    EMBED_TEST_EQ( true, (condition))

#define EXPECT_FALSE(condition) \
    EMBED_TEST_EQ( false, (condition))

/* val1 == val2 */
#define EXPECT_EQ(val1, val2) \
    EMBED_TEST_EQ( (val1), (val2))

/* val1 != val2 */
#define EXPECT_NE(val1, val2) \
    EMBED_TEST_NE( (val1), (val2));

/* val1 < val2 */
#define EXPECT_LT(val1, val2) \
    EMBED_TEST_LT( (val1), (val2))

/* val1 <= val2 */
#define EXPECT_LE(val1, val2) \
    EMBED_TEST_LE( (val1), (val2))

/* val1 > val2 */
#define EXPECT_GT(val1, val2) \
    EMBED_TEST_GT( (val1), (val2))

/* val1 >= val2*/
#define EXPECT_GE(val1, val2) \
    EMBED_TEST_GE( (val1), (val2))

#define EXPECT_STREQ(expected_str, actual_str) \
    EMBED_TEST_STR_EQ( expected_str, actual_str)

#define EXPECT_STRNE(expected_str, actual_str) \
    EMBED_TEST_STR_NEQ( expected_str, actual_str)

#define EXPECT_NEAR(val1, val2, abs_error) \
    EMBED_TEST_NEAR( (val1), (val2), (abs_error))

#endif

/*
 * __CDT_PARSER__ never defined in projects, next redefined macros help eclipse CDT parse unit tests
 */
#ifdef __CDT_PARSER__

#if 0
#undef ASSERT_TRUE(condition)
#undef ASSERT_FALSE(condition)
#undef ASSERT_EQ(val1, val2)
#undef ASSERT_NE(val1, val2)
#undef ASSERT_LT(val1, val2)
#undef ASSERT_LE(val1, val2)
#undef ASSERT_GT(val1, val2)
#undef ASSERT_GE(val1, val2)
#undef ASSERT_STREQ(expected_str, actual_str)
#undef ASSERT_STRNE(expected_str, actual_str)
#undef ASSERT_FLOAT_EQ(val1, val2)
#undef ASSERT_DOUBLE_EQ(val1, val2)
#undef EXPECT_TRUE(condition)
#undef EXPECT_FALSE(condition)
#undef EXPECT_EQ(val1, val2)
#undef EXPECT_NE(val1, val2)
#undef EXPECT_LT(val1, val2)
#undef EXPECT_LE(val1, val2)

#undef EXPECT_GE(val1, val2)
#undef EXPECT_STREQ(expected_str, actual_str)
#undef EXPECT_STRNE(expected_str, actual_str)
#undef EXPECT_NEAR(val1, val2, abs_error)

#define TEST_CONDITION(condition) if (condition) {  }
#define TEST_VALUE(val1, val2) if (val1 < val2) {  }
#define TEST_VALUE_ABS(val1, val2, abs_error) if ((val1 - val2) < abs_error) {  }

#define ASSERT_TRUE(condition) TEST_CONDITION(condition)
#define ASSERT_FALSE(condition) TEST_CONDITION(condition)
#define ASSERT_EQ(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_NE(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_LT(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_LE(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_GT(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_GE(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_STREQ(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_STRNE(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_FLOAT_EQ(val1, val2) TEST_VALUE(val1, val2)
#define ASSERT_DOUBLE_EQ(val1, val2) TEST_VALUE(val1, val2)

#define EXPECT_FALSE(condition) TEST_CONDITION(condition)
#define EXPECT_EQ(val1, val2) TEST_VALUE(val1, val2)

#define EXPECT_LT(val1, val2) TEST_VALUE(val1, val2)
#define EXPECT_LE(val1, val2) TEST_VALUE(val1, val2)
#define EXPECT_GT(val1, val2) TEST_VALUE(val1, val2)
#define EXPECT_GE(val1, val2) TEST_VALUE(val1, val2)

#define EXPECT_STRNE(val1, val2) TEST_VALUE(val1, val2)
#define EXPECT_NEAR(val1, val2, abs_error) TEST_VALUE_ABS(val1, val2, abs_error)

#endif


#define EXPECT_EQ_MEM(memL, memR, len)                                                                                 \
    do {                                                                                                               \
        if (0 != memcmp (memL, memR, len)) {                                                                           \
        	rx_printf ("\n%s:Line: %d diffenent memory", __FUNCTION__, __LINE__);                                         \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_TRUE(val_in)                                                                                            \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if (true != ((bool)val)) {                                                                                     \
        	rx_printf ("\n%s:Line: %d in val %d ", __FUNCTION__, __LINE__, (int)val);                                     \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);


#define EXPECT_EQ(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                              \
        /*int val2 = val2; */                                                                                              \
        if (val1 != val2) {                                                                                            \
        	rx_printf ("\n%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                      \
            /*printf ("   val1: 0x%x val2: 0x%x  ", (int)val1, (int)val2);*/                                           \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while (0);


#define EXPECT_STREQ(strL, strR)                                                                                      \
    do {                                                                                                               \
        if (0 != strcmp (strL, strR)) {                                                                                \
        	rx_printf (CRLF"%s:Line: %d in "CRLF"strL: [%s] "CRLF"strR: [%s] ", __FUNCTION__, __LINE__, strL,       \
                    strR);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#endif /* __CDT_PARSER__ */

#endif /* UNIT_TEST_CHECK_H_ */
