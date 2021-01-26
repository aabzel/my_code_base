#include "compiler_test.h"

bool test_text_addr (void) {
    printf ("\n%s()", __FUNCTION__);
    bool res = false;
    char *str1 = "hello, world";
    char *str2 = "hello, world";
    char *str3 = "hello, world3";

    if (str1 != str2) {
        return false;
    } else {
        printf ("\nstr1=%p \nstr2=%p \nstr3=%p", str1, str2, str3);
    }

    if (str3 == str2) {
        return false;
    }

    if (0 != strcmp (str1, str2)) {
        return false;
    }
    test_ro_addr ();
    return true;
}

void test_ro_addr (void) {
    printf ("\n%s()", __FUNCTION__);
    char *str1 = "hello, world";
    char *str2 = "hello, world";

    if (str1 == str2) {
        printf ("\nSame");
    } else {
        printf ("\ndiff");
    }
}
