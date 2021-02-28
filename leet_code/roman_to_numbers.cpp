#include "roman_to_numbers.h"

#include <string>
 #include <unordered_map>

using namespace std;
#if 0
MCMXCIV
1111115
00000
000 0
0 0
#endif

//O(size(text))
int romanToInt(string text) {
	int n = text.length();
	int ans = 0;
	unordered_map<char, int> LookUpTable;
	LookUpTable['I'] = 1;
	LookUpTable['V'] = 5;
	LookUpTable['X'] = 10;
	LookUpTable['L'] = 50;
	LookUpTable['C'] = 100;
	LookUpTable['D'] = 500;
	LookUpTable['M'] = 1000;
	// working the string from back to front and using a map.
	int pos = n - 1;
	int prev_max_val = 0;
	while (0 <= pos) {
		if (prev_max_val <= LookUpTable[text[pos]] ) {
			ans += LookUpTable[text[pos]];
			prev_max_val = LookUpTable[text[pos]];
		} else {
			ans -= LookUpTable[text[pos]];
		}
		pos--;
	}
	return ans;
}

