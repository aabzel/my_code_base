#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void print_vector(vector<vector<int>> &intervals) {
	cout  << endl;
	for (int i=0;i<intervals.size();i++){
		cout  <<"[";
		for(int j=0; j<intervals[i].size();j++){
     		cout << intervals[i].at(j) << ' ';
		}
		cout  <<"]";
	}
	cout  << endl;
	cout  << endl;
}

int removeCoveredIntervals(vector<vector<int>> &intervals) {
	cout << "removeCoveredIntervals(): size" <<intervals.size()<< endl;
	cout << "prio sort" << endl;
	print_vector( intervals);
	sort(intervals.begin(), intervals.end());
	cout << "after sort" << endl;
	print_vector( intervals);
	int n = intervals.size();
	int r = 0;
	for (int i = 0; i < n - 1; i++) {
		if (       (intervals[i][0] <=intervals[i + 1][0])	&&( intervals[i + 1][1] <= intervals[i][1])) {
			// just like [1,4] [2,3]  so -> [1,4] and [2,3] removed
			swap(intervals[i + 1], intervals[i]);
			r += 1;
		} else if ((intervals[i + 1][0] == intervals[i][0])  && (intervals[i][1] < (intervals[i + 1][1]) )) {
			//just like [1,2] [1,4] so [1,4] and [1,2] removed
			r += 1;
	    }
	}
	return n - r;
}
