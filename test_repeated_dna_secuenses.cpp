#include "test_repeated_dna_secuenses.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "repeated_dna_secuenses.h"
#include "uTests.h"

using namespace std;

bool test_findRepeatedDnaSequences (void) {
    cout << __FUNCTION__ << endl;
    vector<string> rep1;
    string share;
    vector<string> rep2;
    share = extract_shared ("TT", "TTT");
    EXPECT_EQ_STR_CPP ("TT", share);

    share = extract_shared ("AAAAACCCCCCAAAAAGGGTTT", "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    EXPECT_EQ_STR_CPP ("AAAAACCCCC", share);

    rep1 = findRepeatedDnaSequences ("GAGAGAGAGAGAG");
    EXPECT_EQ (2, rep1.size ());
    EXPECT_EQ_STR_CPP ("AGAGAGAGAG", rep1[0]);
    EXPECT_EQ_STR_CPP ("GAGAGAGAGA", rep1[1]);

    rep1 = findRepeatedDnaSequences ("");
    EXPECT_EQ (0, rep1.size ());

    rep1 = findRepeatedDnaSequences ("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    EXPECT_EQ (2, rep1.size ());
    EXPECT_EQ_STR_CPP ("AAAAACCCCC", rep1[0]);
    EXPECT_EQ_STR_CPP ("CCCCCAAAAA", rep1[1]);

    rep2 = findRepeatedDnaSequences ("AAAAAAAAAAAAA");
    EXPECT_EQ (1, rep2.size ());
    EXPECT_EQ_STR_CPP ("AAAAAAAAAA", rep2[0]);

    return true;
}

bool test_findRepeatedDnaSequences1 (void) {
    cout << __FUNCTION__ << endl;
    vector<string> rep1;
    string share;
    vector<string> rep2;

    rep1 = findRepeatedDnaSequences1 ("GAGAGAGAGAGAG");
    EXPECT_EQ (2, rep1.size ());
    EXPECT_EQ_STR_CPP ("AGAGAGAGAG", rep1[0]);
    EXPECT_EQ_STR_CPP ("GAGAGAGAGA", rep1[1]);

    rep1 = findRepeatedDnaSequences1 ("");
    EXPECT_EQ (0, rep1.size ());

    rep1 = findRepeatedDnaSequences1 ("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    EXPECT_EQ (2, rep1.size ());
    EXPECT_EQ_STR_CPP ("AAAAACCCCC", rep1[0]);
    EXPECT_EQ_STR_CPP ("CCCCCAAAAA", rep1[1]);

    rep2 = findRepeatedDnaSequences1 ("AAAAAAAAAAAAA");
    EXPECT_EQ (1, rep2.size ());
    EXPECT_EQ_STR_CPP ("AAAAAAAAAA", rep2[0]);

    return true;
}
