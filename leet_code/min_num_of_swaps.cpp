#include "min_num_of_swaps.h"

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

static int min_int(int val1, int val2) {
  int outVal = val2;
  if (val1 < val2) {
    outVal = val1;
  }
  return outVal;
}

static int min_swaps_dynamic(vector <int> arr, int cur_sw_cnt){
#ifdef DEBUG_MIN_SWAPS
	cout << __FUNCTION__<< " cur_swap_cnt: "<<cur_sw_cnt<<endl;
#endif
	int min_swaps =INT_MAX ;
	int n = arr.size();
	bool was_swap=false;
	int total_swap = INT_MAX ;
	int cur_total_swap = 0;
	vector <int> orig_arr;
	int orig_cur_sw_cnt = 0;
	for(int first=0; first<n; first++) {
  	  for(int second=0; second<n; second++) {
          orig_arr = arr;
		  orig_cur_sw_cnt = cur_sw_cnt;
		  if((first !=second) && (first<second) && (orig_arr[first] < orig_arr[second])){
#ifdef DEBUG_MIN_SWAPS
			  cout << " ["<< first<<"]:"<< orig_arr[first]<<" ["<<second<<"]:"<<orig_arr[second] << endl;
#endif			  
			  iter_swap(orig_arr.begin() +first, orig_arr.begin() + second);
			  was_swap = true;
			  orig_cur_sw_cnt++;
			  cur_total_swap = min_swaps_dynamic(orig_arr,  orig_cur_sw_cnt);
			  total_swap = min_int(cur_total_swap, total_swap);
		  }
	  }
	}
	if (false==was_swap) {
		total_swap = cur_sw_cnt;
	}
	return total_swap;
}

int minSwaps(vector <int> arr) {
		cout << __FUNCTION__<< endl;
	int swap = min_swaps_dynamic(arr,0);
	return swap;
}

