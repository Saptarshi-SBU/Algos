/*------------------------------------------------------------------------
 *
 * Two Sum
 *
 *
 * -----------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {

public:

    vector<int> twoSum(vector<int>& nums, int target) {
        int f = 0;
        int r = nums.size() - 1;

        std::sort(nums.begin(), nums.end());

        while (f < r) {
            int sum = nums.at(f) + nums.at(r);
            if (target == sum) {
                    return vector<int> {f, r};                
            } else if (sum > target) {
                    r--;
            } else {
                    f++;
            }
        }
        return vector<int>(2, -1);
    }

	// O(n)
    vector<int> twoSumH(vector<int>& nums, int target) {
	int pos = 0;	
	unordered_map<int, int> map;

	for (auto i : nums) {
		if (map.find(target - i) != map.end()) {
			return vector<int> {pos, map[target - i]};
		} else
			map[i] = pos++;
	}
        return vector<int>(2, -1);
    }	

    vector<int> threeSum(vector<int>& nums, int target) {
		
        int f = 0;
        int r = nums.size() - 1;

        std::sort(nums.begin(), nums.end());
	while (f < r) {
		int delta = target - (nums.at(f) + nums.at(r));

		if (delta < nums.at(f)) {
			r--;
		} else if (delta > nums.at(r)) {
			f++;
		} else {

			int low  = f + 1;
			int high = r - 1;
			int mid  = f + 1;
			while (low < high) {
				int mid = low + (high - low)/2;
				if (nums.at(mid) == delta)
					return vector<int> {f, mid, r};
				else if (nums.at(mid) > delta)
					high = mid - 1;
				else
					low = low + 1;
			}

			if (mid == f + 1)
				f++;
			else 
				r--;
		}
	}
	return vector<int> (3, -1);
    }
};

int main(void) {
	const int target = 9;
	vector<int> v = {1, 2, 3, 4, 5, 6};
	Solution *sol = new Solution;
	auto result = sol->twoSum(v, target);
	for (auto i : result)
		cout << i << " ";
	cout << endl;
	result = sol->twoSumH(v, target);
	for (auto i : result)
		cout << i << " ";
	cout << endl;
	result = sol->threeSum(v, target);
	for (auto i : result)
		cout << i << " ";
	cout << endl;
	return 0;
}
