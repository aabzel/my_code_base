#ifndef UNIT_TEST_MACRO_H_
#define UNIT_TEST_MACRO_H_

#include "unit_test_info.h"


#ifdef __ghs__
#pragma ghs nowarning 2101 /* MISRA 2012 Rule 1.2: language extensions are not allowed */
#pragma ghs nowarning 1862 /* MISRA 2012 Rule D4.9: function-like macro not allowed -- use function instead */
#pragma ghs nowarning 1830 /* MISRA 2012 Rule 20.10: # or ## operator not allowed */
#endif

#define PRAGMA(x) _Pragma(#x)

#ifdef   __cplusplus
#define TEST(suite, test_case) \
    extern "C" { \
        static void (ut_##suite##_##test_case)(void); \
        extern const unit_test_info_t _ut_##suite##_##test_case; \
        PRAGMA(ghs reference _ut_##suite##_##test_case) \
        __attribute__((used)) \
        __attribute__((section(".unit_test_info"))) \
        const unit_test_info_t _ut_##suite##_##test_case = { \
            (#suite "." #test_case), (ut_##suite##_##test_case) \
        }; \
    }\
    __attribute__((used)) \
    static void (ut_##suite##_##test_case)(void)
#else
#define TEST(suite, test_case) \
    extern const unit_test_info_t _ut_##suite##_##test_case; \
    static void (ut_##suite##_##test_case)(void); \
    PRAGMA(ghs reference _ut_##suite##_##test_case) \
    __attribute__((used)) \
    __attribute__((section(".unit_test_info"))) \
    const unit_test_info_t _ut_##suite##_##test_case = { \
        (#suite "." #test_case), (ut_##suite##_##test_case) \
    }; \
    static void (ut_##suite##_##test_case)(void)
#endif

#ifdef __ghs__
#pragma ghs endnowarning 1830 /* MISRA 2012 Rule 20.10: # or ## operator not allowed */
#pragma ghs endnowarning 1862 /* MISRA 2012 Rule D4.9: function-like macro not allowed -- use function instead */
#endif


#endif /* UNIT_TEST_MACRO_H_ */
