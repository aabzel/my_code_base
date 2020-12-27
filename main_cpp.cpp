#include <iostream>

#include "uTests.h"

using namespace std;
 
int main(void) {
   cout << "main" << endl;

   bool res= u_tests();
   if (false==res) {
	   cout << "unit tests error!" << endl;
   }else {
	   cout << "unit tests fine!" << endl;
   }

   return 0;
}
