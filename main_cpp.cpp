#include <iostream>

#include "uTests.h"

using namespace std;

int init_by_foo1 (void) {
    cout << BASENAME () << " " << __FUNCTION__ << "() line " << __LINE__ << endl;
    return 1;
}

int init_by_foo2 (void) {
    cout << BASENAME () << " " << __FUNCTION__ << "() line " << __LINE__ << endl;
    return 2;
}

int a_val1 = init_by_foo1 ();
int a_val2 = init_by_foo2 ();

int main (void) {
    cout << "main" << endl;

    bool res = u_tests ();
    if (false == res) {
        cout << "unit tests error!" << endl;
    } else {
        cout << "unit tests fine!" << endl;
    }

    return 0;
}
