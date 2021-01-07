#include "test_number_of_atoms.h"

#include <iostream>

#include "number_of_atoms.h"
#include "uTests.h"

bool test_number_of_atoms (void) {
    cout << __FUNCTION__ << endl;
    string histogram;

    EXPECT_EQ (2, atoi ("2O"));
    EXPECT_EQ (3, atoi ("3)2)2"));

    histogram = formalize_expression ("H2O");
    EXPECT_EQ_STR_CPP (histogram, "(H)2O");

    histogram = formalize_expression ("O3");
    EXPECT_EQ_STR_CPP (histogram, "(O)3");

    histogram = formalize_expression ("Be32");
    EXPECT_EQ_STR_CPP (histogram, "(Be)32");

    histogram = formalize_expression ("H2MgO2");
    EXPECT_EQ_STR_CPP (histogram, "(H)2Mg(O)2");

    histogram = formalize_expression ("K4(ON(SO3)2)2");
    EXPECT_EQ_STR_CPP (histogram, "(K)4(ON(S(O)3)2)2");


#if 1
    histogram = expand_formula ("Be32");
    EXPECT_EQ_STR_CPP (histogram, "BeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBeBe");

    histogram = expand_formula ("Mg(OH)2");
    EXPECT_EQ_STR_CPP (histogram, "MgOHOH");

    histogram = expand_formula ("O3");
    EXPECT_EQ_STR_CPP (histogram, "OOO");

    histogram = expand_formula ("(OH)2");
    EXPECT_EQ_STR_CPP (histogram, "OHOH");

    histogram = expand_formula ("(SO3)2");
    EXPECT_EQ_STR_CPP (histogram, "SOOOSOOO");

    histogram = expand_formula ("(ON(SO3)2)2");
    EXPECT_EQ_STR_CPP (histogram, "ONSOOOSOOOONSOOOSOOO");

    histogram = expand_formula ("K4(ON(SO3)2)2");
    EXPECT_EQ_STR_CPP (histogram, "KKKKONSOOOSOOOONSOOOSOOO");

#endif

    cout << endl << endl << endl << endl;

#if 1

    histogram = countOfAtoms ("K4(ON(SO3)2)2");
    EXPECT_EQ_STR_CPP (histogram,"K4N2O14S4");

    cout << endl<<endl<<endl<<endl;
    histogram = countOfAtoms ("Mg(OH)2");
    EXPECT_EQ_STR_CPP (histogram,"H2MgO2");

    cout << endl<<endl<<endl<<endl;
    histogram = countOfAtoms ("H2O");
    EXPECT_EQ_STR_CPP (histogram,"H2O");


    cout << endl<<endl<<endl<<endl;
    histogram = countOfAtoms ("Be32");
    EXPECT_EQ_STR_CPP (histogram,"Be32");
#endif
    cout << __FUNCTION__ << " Fine" << endl;
    return true;
}
// K4(ON(SO3)2)2
// K4(ON(SOOO)(SOOO))(ON(SOOO)(SOOO))
// K4(ONSOOOSOOO)(ONSOOOSOOO)
// K4(ONSOOOSOOO)(ONSOOOSOOO)
// K4O14NSSNSS
// K4N2O14S4
