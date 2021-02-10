#include "test_generate_parentheses.h"

#include <stdbool.h>
#include <string>
#include <vector>

#include "generate_parentheses.h"
#include "uTests.h"
#include "utils_cpp.h"

bool test_generate_parentheses (void) {
    cout << __FUNCTION__ << endl;
    vector<string> variants;
    variants = generateParenthesis (1);
    EXPECT_EQ_STR_CPP ("()", variants[0]);

    variants = generateParenthesis (2);
    print_vector_strs (variants);
    EXPECT_EQ_STR_CPP ("(())", variants[0]);
    EXPECT_EQ_STR_CPP ("()()", variants[1]);

    variants = generateParenthesis (3);
    print_vector_strs (variants);
    return true;
}
