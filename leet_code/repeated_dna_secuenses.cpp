#include "repeated_dna_secuenses.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils_cpp.h"

using namespace std;

string extract_shared (string a, string b) {
#ifdef DEBUG_DNA
    // cout << __FUNCTION__ <<" a "<< a<<" b "<< b<< endl;
#endif
    string shared;
    int min_size = min (a.size (), b.size ());
    for (int i = 0; i < min_size; i++) {
        if (a[i] == b[i]) {
            shared = shared + b[i];
        } else {
            break;
        }
    }
    return shared;
}

void remove_duplicates (std::vector<string> &vec) {
    sort (vec.begin (), vec.end ());
    vec.erase (unique (vec.begin (), vec.end ()), vec.end ());
}

vector<string> findRepeatedDnaSequences (string in_s) {
#ifdef DEBUG_DNA
    cout << __FUNCTION__ << endl;
#endif
    vector<string> substring_list;
    vector<string> rep_list;
    if (0 < in_s.size ()) {
        int i;
        for (i = 0; i < in_s.size (); i++) {
            substring_list.push_back (&in_s[i]);
        }
        string shared_str;
        sort (substring_list.begin (), substring_list.end ());
#ifdef DEBUG_DNA
        print_vector_strs (substring_list);
#endif
        for (i = 0; i < substring_list.size () - 1; i++) {
#ifdef DEBUG_DNA
            cout << " i " << i << " i+1 " << i + 1 << endl;
            cout << " i " << i << " i+1 " << i + 1 << endl;
            cout << "  1 " << substring_list[i] << endl;
            cout << "  2 " << substring_list[i + 1] << endl;
#endif
            shared_str = extract_shared (substring_list[i], substring_list[i + 1]);
            if (10 <= shared_str.size ()) {
#ifdef DEBUG_DNA
                cout << "  spot " << shared_str << endl;
#endif
                rep_list.push_back (shared_str.substr (0, 10));
            }
        }
#ifdef DEBUG_DNA
        print_vector_strs (rep_list);
#endif
        // remove duplicate fron vector string
        remove_duplicates (rep_list);
#ifdef DEBUG_DNA
        cout << __FUNCTION__ << " End " << endl;
#endif
    }
    return rep_list;
}

vector<string> findRepeatedDnaSequences1 (string text) {
    unordered_map<string, bool> pattern_table;
    set<string> repeated_set;

    string slidind_window;
    for (int i = 0; i <= int (text.size ()) - 10; i++) {
        slidind_window = text.substr (i, 10);
        if (pattern_table.find (slidind_window) == pattern_table.end ())
            pattern_table[slidind_window] = true;
        else
            repeated_set.insert (slidind_window);
    }

    vector<string> rvec (repeated_set.begin (), repeated_set.end ());
    return rvec;
}
