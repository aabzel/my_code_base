#include "number_of_atoms.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;
vector<string> periodicTable = {
    "H",  "He", "Li", "Be", "B",  "C",  "N",  "O",  "F",  "Ne", "Na", "Mg", "Al", "Si", "P",  "S",  "Cl",
    "Ar", "K",  "Ca", "Sc", "Ti", "V",  "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se",
    "Br", "Kr", "Rb", "Sr", "Y",  "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb",
    "Te", "I",  "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er",
    "Tm", "Yb", "Lu", "Hf", "Ta", "W",  "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At",
    "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U",  "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No",
    "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"};

void computeLPSArray (string pat, int M, int lps[]) {

    // Length of the previous longest
    // prefix suffix
    int len = 0;
    int i = 1;
    lps[0] = 0; // lps[0] is always 0

    // The loop calculates lps[i] for
    // i = 1 to M-1
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else // (pat[i] != pat[len])
        {

            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not
                // increment i here
            } else // if (len == 0)
            {
                lps[i] = len;
                i++;
            }
        }
    }
}

int KMPSearch (string pat, string txt) {
    int M = pat.length ();
    int N = txt.length ();

    // Create lps[] that will hold the longest
    // prefix suffix values for pattern
    int lps[M];
    int j = 0; // index for pat[]

    // Preprocess the pattern (calculate lps[]
    // array)
    computeLPSArray (pat, M, lps);

    int i = 0; // index for txt[]
    int res = 0;
    int next_i = 0;

    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {

            // When we find pattern first time,
            // we iterate again to check if there
            // exists more pattern
            j = lps[j - 1];
            res++;

            // We start i to check for more than once
            // appearance of pattern, we will reset i
            // to previous start+1
            if (lps[j] != 0)
                i = ++next_i;
            j = 0;
        }

        // Mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {

            // Do not match lps[0..lps[j-1]]
            // characters, they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return res;
}

// expand the formula to full view   Mg(OH)2->MgOHOH
// count each atom
string build_histogram (string expand_formula) {
    cout << __FUNCTION__ << " [" << expand_formula << "] " << endl;
    string res_hist = "";
    sort (periodicTable.begin (), periodicTable.end ());
    for (unsigned int i = 0; i < periodicTable.size (); i++) {
        int num = KMPSearch (periodicTable[i], expand_formula);
        if (1 < num) {
            res_hist += periodicTable[i] + to_string (num);
        } else if (1 == num) {
            res_hist += periodicTable[i];
        }
    }
    return res_hist;
}
int calc_digits (int num) {
    int digits = 1;
    if (10 <= num) {
        digits = 2;
    }
    if (100 <= num) {
        digits = 3;
    }
    return digits;
}

// string countOfAtoms (string formula){
//	int nest=calc_amount_of_nesting(formula);
//}
bool is_formalize_expression (string formula) {
    bool res = true;
    for (int i = 0; i <= formula.size (); i++) {
        char c = formula[i];
        if (isdigit (c)) {
            if (isalpha (formula[i - 1])) {
                res = false;
            }
        }
    }
    return res;
}

string formalize_expression (string formula) {
    string res = "";
    char next = '\0';
    char next_2 = '\0';
    char cur = '\0';
    char prev = '\0';
    for (int i = 0; i < formula.size (); i++) {
        // cout << endl<< endl <<"proc"<< i <<" "<<formula[i] << endl;
        char cur = formula[i];
        if (i < formula.size () - 1) {
            next = formula[i + 1];
            next_2 = formula[i + 2];
        } else {
            next = '\0';
        }
        if (isalpha (cur)) {
            if (isupper (cur)) {
                // O
                if (isdigit (next)) {
                    res.push_back ('(');
                    res.push_back (cur);
                    res.push_back (')');
                } else if (isdigit (next_2) && islower (next)) {
                    res.push_back ('(');
                    res.push_back (cur);
                    res.push_back (next);
                    res.push_back (')');
                    i++;
                } else {
                    res.push_back (cur);
                }
            } else {
                // e
                if (isdigit (next)) {
                    res.push_back (cur);
                } else {
                    res.push_back (cur);
                }
            }
        } else if (isdigit (cur)) {
            res.push_back (cur);
        } else {
            res.push_back (cur);
        }
        prev = cur;
    }
    return res;
}

#if 0

string expand_formula(string formula){

}
#endif

#if CORRECT
string countOfAtoms (string formula) {
    map<string, int> m;
    stack<pair<string, int>> st;

    string curr = ""; // Building symbols
    int num = 0;      // Counting
    int i = 0;        // Index

    while (i < formula.size ()) {
        char c = formula[i];
        if (c == '(') {
            // Open Bracket
            curr = "";
            num = 0;
            st.emplace ("(", 0);
            ++i;
        }

        else if (c == ')') {
            stack<pair<string, int>> temp;
            ++i;

            // Scan past the last paren to see if we have any numbers
            while (i < formula.size () && isdigit (formula[i])) {
                num = num * 10 + (formula[i] - '0');
                ++i;
            }
            // Multiply everything in between
            while (st.top ().first != "(") {

                // num is 0 to make parsing work, but no num after symbols means 1

                temp.emplace (st.top ().first, st.top ().second * max (1, num));
                st.pop ();
            }

            // reset
            num = 0;

            // Get rid of open Paren
            st.pop ();

            // Put stuff back
            while (!temp.empty ()) {
                st.emplace (temp.top ());
                temp.pop ();
            }
        }

        else if (isupper (c)) {
            // Parse Symbol plus immediate numbers

            curr += c;
            ++i;
            while (i < formula.size () && islower (formula[i])) {
                curr += formula[i];
                ++i;
            }
            while (i < formula.size () && isdigit (formula[i])) {
                num = num * 10 + formula[i] - '0';
                ++i;
            }
            st.emplace (curr, max (1, num));
            curr = "", num = 0;
        }
    }

    // Add everything
    while (!st.empty ()) {
        m[st.top ().first] += st.top ().second;
        st.pop ();
    }

    // Already have a string around
    curr = "";

    for (auto &p : m) {
        curr += p.first;
        if (p.second > 1)
            curr += to_string (p.second);
    }
    return curr;
}
#endif

#if 1

//"K4(ON(SO3)2)2"
string expand_formula (string formula) {
    formula = formalize_expression (formula);
    cout << __FUNCTION__ << " [" << formula << "] " << endl;
    string out_res = "";
    string temp_res = "";
    string cur_str = "";
    string tmp_str, temp_str;
    // string  prefix_str;
    int round_bracket_open = 0;
    int round_bracket_closed = 0;
    int stack_depth = 0;
    stack<string> stack_stack;
    stack<string> stack_prefix;
    int num = 0;
    for (unsigned int i = 0; i < formula.size (); i++) {
        cout << endl << "proc {" << formula[i] << "}";
        cout << " cur_str {" << cur_str << "}";
        if (1 <= stack_prefix.size ()) {
            cout << " stack_prefix {" << stack_prefix.top () << "} size: " << stack_prefix.size ();
        }

        if (1 <= stack_stack.size ()) {
            cout << " stack_top {" << stack_stack.top () << "} size: " << stack_stack.size ();
        }
        cout << endl;
        switch (formula[i]) {
        case '(': {
            stack_depth++;
            round_bracket_open++;
            // prefix_str=cur_str;
            cout << " save prefix before ( {" << cur_str << "}";
            stack_prefix.push (cur_str);
            cur_str = "";
        } break;
        case ')': {
            string tmp;
            stack_depth--;
            round_bracket_closed++;
            if (1 <= stack_stack.size ()) {
                tmp = stack_stack.top ();
                cout << "    push after ) [" << tmp << "]" << endl;
                stack_stack.push (tmp);
            } else {
                cout << "    push after ) [" << cur_str << "]" << endl;
                stack_stack.push (cur_str);
            }
            // if(1<=stack_stack.size()) {
            //	tmp_str = stack_stack.top();stack_stack.pop();
            //	cout <<"    top after ) ["<< tmp_str<<"]" << endl;
            //}
            cur_str = "";
        } break;
        default: {
            if (isalpha (formula[i])) {
                cur_str = cur_str + formula[i];
                if (isdigit (formula[i + 1])) {
                    cout << "    push [" << cur_str << "]" << endl;
                    stack_stack.push (cur_str);
                    cur_str = "";
                }

            } else {
                cout << "    number! " << endl;
                string expand_element = "";
                num = atoi (&formula[i]);
                cout << "    num " << num << endl;
                temp_str = "";
                if (1 <= stack_stack.size ()) {
                    cout << "        stack_stack contain [" << stack_stack.top () << "]" << endl;
                    temp_str = stack_stack.top ();
                    stack_stack.pop ();
                    cout << "    num " << num << "*" << temp_str << endl;
                    for (int j = 0; j < num; j++) {
                        cout << cur_str << endl;
                        expand_element = expand_element + temp_str;
                    }
                }

                cout << "     expand_element " << expand_element << " depth " << stack_depth << endl;
                cur_str = expand_element;

                if (0 == stack_depth) {
                    out_res += expand_element;
                    cout << "     out_res " << out_res << endl;
                } else {
                    if (0 < stack_prefix.size ()) {
                        cout << "   middle push [" << stack_prefix.top () << "+" << cur_str << "]" << endl;
                        stack_stack.push (stack_prefix.top () + cur_str);
                        stack_prefix.pop ();

                    } else {
                        cout << "   middle push [" << cur_str << "]" << endl;
                        stack_stack.push (cur_str);
                    }
                }

                // out_res +=cur_str;
                cur_str = "";
                if (1 < calc_digits (num)) {
                    i = i + calc_digits (num) - 1;
                }
            }
        } break;
        }
    }
    cout << "End" << endl;
#if 0
	while(1<=stack_stack.size()) {
		cout << " prefix size "<<stack_stack.size() << endl;
	    cout << " stack_top {"<< stack_stack.top()<<"}" ;
	    cur_str=stack_stack.top()+cur_str;
	    stack_stack.pop();
	}
#endif
    out_res += cur_str;
    return out_res;
}
#endif
