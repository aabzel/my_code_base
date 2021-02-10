#include "generate_parentheses.h"

#include <algorithm>
#include <string>
#include <vector>

#include "str_ops.h"

using namespace std;

static void compose_sequence_of_brackets (string curr, string append, int size, vector<string> &sequence_of_brackets) {
    if (curr.size () < size) {
        curr += append;
        compose_sequence_of_brackets (curr, "(", size, sequence_of_brackets);
        compose_sequence_of_brackets (curr, ")", size, sequence_of_brackets);
    } else {
        bool res = is_valid_parentheses (curr.c_str ());
        if (true == res) {
            if (find (sequence_of_brackets.begin (), sequence_of_brackets.end (), curr) ==
                sequence_of_brackets.end ()) {
                /* v does not contain x */
                sequence_of_brackets.push_back (curr);
            }
        }
    }
}

vector<string> generateParenthesis (int n) {
    vector<string> sequence_of_brackets;
    string curr = "";
    compose_sequence_of_brackets (curr, "(", n * 2, sequence_of_brackets);
    compose_sequence_of_brackets (curr, ")", n * 2, sequence_of_brackets);
    return sequence_of_brackets;
}
