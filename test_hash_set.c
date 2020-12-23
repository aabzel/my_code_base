#include "test_hash_set.h"

#include <stdio.h>

#include "hash_set.h"
#include "uTests.h"

static bool test_hash_set_case1 (void) {
    HashSet_t *hSet = HashSetCreate ();

    EXPECT_TRUE (HashSetAdd (hSet, 3));
    EXPECT_TRUE (HashSetContains (hSet, 3));

    EXPECT_TRUE (HashSetAdd (hSet, 4));
    EXPECT_TRUE (HashSetContains (hSet, 4));

    EXPECT_TRUE (HashSetAdd (hSet, 5));
    EXPECT_TRUE (HashSetContains (hSet, 5));

    EXPECT_TRUE (HashSetRemove (hSet, 4));
    EXPECT_FALSE (HashSetContains (hSet, 4));

    EXPECT_TRUE (HashSetFree (hSet));

    return true;
}

bool test_hash_set (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_TRUE (test_hash_set_case1 ());
    return true;
}
