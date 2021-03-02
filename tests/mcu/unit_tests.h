#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


#define EXPECT_EQ_STR(strL, strR)                                                                                      \
    do {                                                                                                               \
        if (0 != strcmp (strL, strR)) {                                                                                \
            printf ("\n%s:Line: %d %d in \nstrL: [%s] \nstrR: [%s] ", __FUNCTION__, __LINE__, __COUNTER__, strL,       \
                    strR);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);


size_t basename_start (const char *filename);
#define BASENAME() ((__FILE__ ":") + basename_start (__FILE__))



#define EXPECT_EQ_STR_LEN(strL, strR, len)                                                                             \
    do {                                                                                                               \
        if (0 != strncmp (strL, strR, len)) {                                                                          \
            printf ("\n%s:Line: %d %d in \nstrL: [%s] \nstrR: [%s] ", __FUNCTION__, __LINE__, __COUNTER__, strL,       \
                    strR);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);


#define EXPECT_EQ_MEM(memL, memR, len)                                                                                 \
    do {                                                                                                               \
        if (0 != memcmp (memL, memR, len)) {                                                                           \
            printf ("\n%s:Line: %d diffenent memory", __FUNCTION__, __LINE__);                                         \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_NE(val1, val2)                                                                                          \
    do {                                                                                                               \
        if (val1 == val2) {                                                                                            \
            printf ("\n%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                      \
            printf ("   val1: 0x%x val2: 0x%x  ", (int)val1, (int)val2);                                               \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_NULL(val)                                                                                               \
    do {                                                                                                               \
        if (0 != val) {                                                                                                \
            printf ("\n%s():Line: %d in  val: %u ", __FUNCTION__, __LINE__, val);                                      \
            return val;                                                                                                \
        }                                                                                                              \
    } while (0);

#define EXPECT_EQ(vala, valb)                                                                                          \
    do {                                                                                                               \
        int val1 = vala;                                                                                               \
        int val2 = valb;                                                                                               \
        if (val1 != val2) {                                                                                            \
            printf ("\n%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                      \
            /*printf ("   val1: 0x%x val2: 0x%x  ", (int)val1, (int)val2);*/                                           \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while (0);

#define EXPECT_HEX_EQ(val1, val2)                                                                                      \
    do {                                                                                                               \
        if (val1 != val2) {                                                                                            \
            printf ("\n%s:Line: %d %d in val1: %x val2: %x ", __FUNCTION__, __LINE__, __COUNTER__, (int)val1,          \
                    (int)val2);                                                                                        \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_TRUE(val_in)                                                                                            \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if (true != ((bool)val)) {                                                                                     \
            printf ("\n%s:Line: %d in val %d ", __FUNCTION__, __LINE__, (int)val);                                     \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_FALSE(val)                                                                                              \
    do {                                                                                                               \
        if (false != val) {                                                                                            \
            printf ("\n%s:Line: %d val %d ", __FUNCTION__, __LINE__, (int)val);                                        \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

bool run_unit_test (void);

#endif /* UNIT_TESTS_H */
