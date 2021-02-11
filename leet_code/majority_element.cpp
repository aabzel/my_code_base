#include "majority_element.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct num_raiting{
	int val;
	int cnt;
};

static num_raiting update_majority(num_raiting num_a, num_raiting num_b){
	num_raiting val=num_b;
	if(num_b.cnt < num_a.cnt){
		val=num_a;
	}
	return val;
}

int majority_element (vector<int>& nums) {
    cout << __FUNCTION__ << endl;
	sort(nums.begin(),nums.end());
	int prev=-1;
	num_raiting majority_el={0,0};
	num_raiting cur_majority_el={nums[0],1};

	majority_el.val=nums[0];
	majority_el.cnt=1;

	for(int i=0;i<nums.size(); i++){
		if((prev==nums[i])  && (1<=i)){
			cur_majority_el.val=nums[i];
			cur_majority_el.cnt++;
			//
			majority_el=update_majority(majority_el,cur_majority_el);
		}else{
			cur_majority_el.val=nums[i];
			cur_majority_el.cnt=1;
		}
		prev=nums[i];
	}
	return majority_el.val;
}
