#include "bulls_and_cows.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>

#include <stdint.h>

#include "utils_cpp.h"

using namespace std;

struct number {
    char letter;
    uint32_t pos;
};

inline bool operator< (const number &lhs, const number &rhs) {
    bool res = false;
    if (lhs.letter < rhs.letter) {
        res = true;
    } else if (lhs.letter == rhs.letter) {
        if (lhs.pos < rhs.pos) {
            res = true;
        } else if (lhs.pos == rhs.pos) {
            res = false;
        } else {
            res = false;
        }
    } else {
        res = false;
    }
    return res;
}

#ifdef DEBUG_BULLS_COWS
template <class Type> void print_vector (vector<Type> words) {
    // cout << __FUNCTION__ << endl;
    cout << endl;
    for (uint32_t i = 0; i < words.size (); i++) {
        cout << "[";
        cout << words[i] << ' ';
        cout << "]" << endl;
    }
    cout << endl;
}
#endif

int count_max_cows (string secret, string guess) {
#ifdef DEBUG_BULLS_COWS
    cout << __FUNCTION__ << " " << secret << " " << guess << endl;
#endif
    int max_pos_cows = 0;
    vector<char> guess_vector;
    for (uint32_t i = 0; i < guess.size (); i++) {
        guess_vector.push_back (guess[i]);
    }

    for (uint32_t i = 0; i < secret.size (); i++) {
        // secret[i]
#ifdef DEBUG_BULLS_COWS
        print_vector (guess_vector);

        cout << " [d] Explore " << secret[i] << " " << guess << endl;
#endif

        auto it = find (guess_vector.begin (), guess_vector.end (), secret[i]);
        // check that there actually is a 3 in our vector
        if (it != guess_vector.end ()) {
            guess_vector.erase (it);
            max_pos_cows++;
        }
    }

    return max_pos_cows;
}

string getHint (string secret, string guess) {
    // load
#ifdef DEBUG_BULLS_COWS
    cout << __FUNCTION__ << " " << secret << " " << guess << endl;
#endif
    set<number> bulls_set;
    set<char> nums_set;
    int max_cows = count_max_cows (secret, guess);
    for (uint32_t i = 0; i < secret.size (); i++) {
        number num = {secret[i], i};
        bulls_set.insert (num);
        nums_set.insert (secret[i]);
    }
    //
    // using begin() to print set
#ifdef DEBUG_BULLS_COWS
    cout << "bull set: " << endl;
    for (auto it = bulls_set.begin (); it != bulls_set.end (); it++) {
        cout << " " << (*it).letter << " " << (*it).pos << endl;
    }
#endif

#ifdef DEBUG_BULLS_COWS
    cout << "bull set end " << endl;

    // using begin() to print set
    cout << "nums_set: " << endl;
    for (auto it = nums_set.begin (); it != nums_set.end (); it++) {
        cout << " " << (*it) << " " << endl;
    }
    cout << "nums_set " << endl;
#endif
    int cows = 0;
    int bulls = 0;
    set<number>::iterator it_bull;
    set<char>::iterator it_cow;

    for (uint32_t i = 0; i < guess.size (); i++) {
#ifdef DEBUG_BULLS_COWS
        cout << "explore " << guess[i] << " " << i << endl;
#endif
        number num = {guess[i], i};
        it_bull = bulls_set.find (num);
        if (it_bull != bulls_set.end ()) {
#ifdef DEBUG_BULLS_COWS
            cout << " [!] Spot bull " << guess[i] << " " << i << endl;
#endif
            max_cows--;
            bulls++;
        }
    }

    for (uint32_t i = 0; i < guess.size (); i++) {
#ifdef DEBUG_BULLS_COWS
        cout << "explore " << guess[i] << " " << i << endl;
#endif
        number num = {guess[i], i};
        it_bull = bulls_set.find (num);
        if (it_bull != bulls_set.end ()) {
        } else {
            it_cow = nums_set.find ((char)guess[i]);
            if (it_cow != nums_set.end ()) {
                if (0 < max_cows) {
#ifdef DEBUG_BULLS_COWS
                    cout << "  [!] Spot cow " << guess[i] << " " << i << endl;
#endif
                    cows++;
                    max_cows--;
                }
            }
        }
    }

    string hint = "" + int_to_string (bulls) + "A" + int_to_string (cows) + "B";

    return hint;
}
