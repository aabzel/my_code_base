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

vector<string> compose_set (string expand_formula) {
    vector<string> set;
    string elem;
    for (int i = 0; i < expand_formula.size (); i++) {
        if (isupper (expand_formula[i])) {
            set.push_back (elem);
            elem = "";
            elem += expand_formula[i];
        } else {
            elem += expand_formula[i];
        }
    }
    set.push_back (elem);
    // for (int j=0; j<set.size(); j++) {
    //     cout << " j:"<<j<<"," <<set[j] << endl;
    //}
    return set;
}

// expand the formula to full view   Mg(OH)2->MgOHOH
// count each atom
string build_histogram (string expand_formula) {
    // cout << __FUNCTION__ << " [" << expand_formula << "] " << endl;
    string res_hist = "";
    vector<string> set;
    set = compose_set (expand_formula);

    sort (periodicTable.begin (), periodicTable.end ());
    for (unsigned int i = 0; i < periodicTable.size (); i++) {
        int num = 0;
        for (int j = 0; j < set.size (); j++) {
            if (set[j] == periodicTable[i]) {
                num++;
            }
        }
        // int num = KMPSearch (periodicTable[i], expand_formula);
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

//"K4(ON(SO3)2)2"
string expand_formula (string formula) {
    formula = formalize_expression (formula);
    // cout << __FUNCTION__ << " [" << formula << "] " << endl;
    string out_res = "";
    string temp_res = "";
    string cur_str = "";
    string tmp_str, temp_str;
    string prefix_str;
    int round_bracket_open = 0;
    int round_bracket_closed = 0;
    int stack_depth = 0;
    stack<string> stack_stack;
    stack<string> stack_prefix;
    int num = 0;
    for (unsigned int i = 0; i < formula.size (); i++) {
        // cout << endl << "proc {" << formula[i] << "}";
        // cout << " cur_str {" << cur_str << "}";
        if (1 <= stack_prefix.size ()) {
            // cout << " stack_prefix {" << stack_prefix.top () << "} size: " << stack_prefix.size ();
        }

        if (1 <= stack_stack.size ()) {
            // cout << " stack_top {" << stack_stack.top () << "} size: " << stack_stack.size ();
        }
        // cout << endl;
        switch (formula[i]) {
        case '(': {
            stack_depth++;
            round_bracket_open++;
            // prefix_str=cur_str;
            // cout << " save prefix before ( {" << cur_str << "}";
            stack_prefix.push (cur_str);
            cur_str = "";
        } break;
        case ')': {
            string tmp;
            stack_depth--;
            round_bracket_closed++;
            if (1 <= stack_stack.size ()) {
                tmp = stack_stack.top ();
                // cout << "    push after ) [" << tmp << "]" << endl;
                stack_stack.push (tmp);
            } else {
                // cout << "    push after ) [" << cur_str << "]" << endl;
                stack_stack.push (cur_str);
            }
            // if(1<=stack_stack.size()) {
            //	tmp_str = stack_stack.top();stack_stack.pop();
            //	//cout <<"    top after ) ["<< tmp_str<<"]" << endl;
            //}
            cur_str = "";
        } break;
        default: {
            if (isalpha (formula[i])) {
                cur_str = cur_str + formula[i];
                if (isdigit (formula[i + 1])) {
                    // cout << "    push [" << cur_str << "]" << endl;
                    stack_stack.push (cur_str);
                    cur_str = "";
                }
                if (0 == stack_depth) {
                    prefix_str + prefix_str + formula[i];
                    // cout << "    prefix_str [" << prefix_str << "]" << endl;
                }

            } else {
                // cout << "    number! " << endl;
                string expand_element = "";
                num = atoi (&formula[i]);
                // cout << "    num " << num << endl;
                temp_str = "";
                if (1 <= stack_stack.size ()) {
                    // cout << "        stack_stack contain [" << stack_stack.top () << "]" << endl;
                    temp_str = stack_stack.top ();
                    stack_stack.pop ();
                    // cout << "    num " << num << "*" << temp_str << endl;
                    for (int j = 0; j < num; j++) {
                        // cout << cur_str << endl;
                        expand_element = expand_element + temp_str;
                    }
                }
#ifdef DEBUG
                cout << "     expand_element " << expand_element << " depth " << stack_depth << endl;
#endif
                cur_str = expand_element;

                if (0 == stack_depth) {
                    out_res += expand_element;
                    // cout << "     out_res " << out_res << endl;
                } else {
                    if (0 < stack_prefix.size ()) {
                        // cout << "   middle push [" << stack_prefix.top () << "+" << cur_str << "]" << endl;
                        stack_stack.push (stack_prefix.top () + cur_str);
                        stack_prefix.pop ();

                    } else {
#ifdef DEBUG
                        cout << "   middle push [" << cur_str << "]" << endl;
#endif
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
#ifdef DEBUG
    cout << "End" << endl;
#endif
    out_res = out_res + cur_str;
#if 1
    while (1 <= stack_prefix.size ()) {
        // cout << "   in cur_str {"<< out_res<<"}" ;
        string prefx = stack_prefix.top ();
#ifdef DEBUG
        cout << " add prefix size " << stack_prefix.size () << endl;
        cout << " stack stack_prefix {" << prefx << "}";
#endif
        stack_prefix.pop ();
        out_res = prefx + out_res;
#ifdef DEBUG
        cout << "   cur_str {" << out_res << "}";
#endif
    }
#endif
    // cout << "   out_res {"<< out_res<<"}" ;
    // cout << " out  out_res   "<<out_res<< endl;
    return out_res;
}

string countOfAtoms (string formula) {
    string expanded = expand_formula (formula);
    string hist = build_histogram (expanded);
    return hist;
}
