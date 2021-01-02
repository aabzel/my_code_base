#include "test_hash_set.h"

#include <stdio.h>

#include "hash_set.h"
#include "uTests.h"

static bool test_hash_set_case1 (void) {
    MyHashSet *hSet = myHashSetCreate ();

    EXPECT_TRUE (myHashSetAdd (hSet, 3));
    EXPECT_TRUE (myHashSetContains (hSet, 3));

    EXPECT_TRUE (myHashSetAdd (hSet, 4));
    EXPECT_TRUE (myHashSetContains (hSet, 4));

    EXPECT_TRUE (myHashSetAdd (hSet, 5));
    EXPECT_TRUE (myHashSetContains (hSet, 5));

    EXPECT_TRUE (myHashSetRemove (hSet, 4));
    EXPECT_FALSE (myHashSetContains (hSet, 4));

    EXPECT_TRUE (myHashSetFree (hSet));

    return true;
}

//["MyHashSet","add","add","contains","contains","add","contains","remove","contains"]
//         [[],[1],[2],    [1],       [3],       [2],    [2],     [2],     [2]]
static bool test_hash_set_case2 (void) {
    MyHashSet *hSet = myHashSetCreate ();

    EXPECT_TRUE (myHashSetAdd (hSet, 1));
    EXPECT_TRUE (myHashSetAdd (hSet, 2));

    EXPECT_TRUE (myHashSetContains (hSet, 1));
    EXPECT_FALSE (myHashSetContains (hSet, 3));

    EXPECT_TRUE (myHashSetAdd (hSet, 2));
    EXPECT_TRUE (myHashSetContains (hSet, 2));

    EXPECT_TRUE (myHashSetRemove (hSet, 2));
    EXPECT_FALSE (myHashSetContains (hSet, 2));

    EXPECT_TRUE (myHashSetFree (hSet));

    return true;
}

bool test_hash_set (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_TRUE (test_hash_set_case1 ());
    EXPECT_TRUE (test_hash_set_case2 ());
    return true;
}
