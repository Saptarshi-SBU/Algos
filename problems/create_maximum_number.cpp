/*
 * Get largest possible number with K digits from given two arrays
 * 
 * Complexity : O(K(M+ N))
 * Space Complexity : O(K)
 *
 * https://leetcode.com/submissions/detail/411210502/
 */

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
   
// using stack based approach to form digits in increasing order
// We pop any element which is lesser than the current one till
// the one which is at the top is the greatest.
// if any remaining digits are left, we trim from the stack top
// so left->right digits are maximized
std::vector<int>
maximizeNumber(vector<int> &nums, int k) {
	size_t i = 0;
	vector<int> ans;
	stack<int> num_stack;
        if (k <= 0)
            return ans;

	int curr = -1;
	int d = nums.size() - k;
	//std::cout << "d:" << d << std::endl;
	while (i < nums.size()) {
		if (curr < 0) {
		    curr = nums.at(i);
		    num_stack.push(nums.at(i));
		} else {
		    curr = nums.at(i);
		    if (d > 0 && !num_stack.empty() && (curr > num_stack.top())) {
			num_stack.pop();
			d--;
			continue;
		    }
		    num_stack.push(curr);
		}
		i++;
	}

	while (d > 0) {
	    num_stack.pop();
	    d--;
	}

	while (!num_stack.empty()) {
	    ans.push_back(num_stack.top());
	    num_stack.pop();
	}

	reverse(ans.begin(), ans.end());
	return ans;
}

// https://medium.com/@dreamume/leetcode-321-create-maximum-number-45af2be1d47d
bool greater(vector<int>& nums1, int i, vector<int>& nums2, int j) {
  while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
    ++i;
    ++j;
  }
  return j == nums2.size() || (i < nums1.size() && nums1[i] > nums2[j]);
}

// Note : you are applying merge sort on this when the arrays are not sorted
std::vector<int>
maximizeNumberByMerge(vector<int> &nums1, vector<int>& nums2, int k) {
	vector<int> ans;
	size_t i = 0, j = 0;
	// bug in merging, I was using min of two arrays to check between i and j
	while (k > 0 && i < nums1.size() && j < nums2.size()) {
	    // special case : there are cases where if elements are equal
            // we need to check follow up parameters to decide which index
	    // to advance to maximize the digit, since arrays are not sorted
            // std::vector<int> a{6, 4, 4, 0};
            // std::vector<int> b{7, 3, 8, 0, 6, 5, 7, 6, 2};
            // vector<int> a {6,7};
            // vector<int> b {6,0,4};
	    if (nums1[i] == nums2[j]) {
		if (greater(nums1, i, nums2, j))
                    ans.push_back(nums1[i++]);
                else
                    ans.push_back(nums2[j++]);
	    } else if (nums1[i] < nums2[j]) {
               ans.push_back(nums2[j++]);
	    } else {
               ans.push_back(nums1[i++]);
	    }
	    k--;
	}

	while (k > 0) {
	     if (i < nums1.size())
		     ans.push_back(nums1.at(i++));
	     else if (j < nums2.size())
		     ans.push_back(nums2.at(j++));
	     k--;
	}
	std::cout << nums1.size() << ":" << nums2.size() << std::endl;
	return ans;
}

vector<int>& compareVectors(vector<int>&num1, vector<int>&num2) {
	if (num1 == num2)
	    return num1;
	else if (num1.size() > num2.size())
	    return num1;
	else if (num1.size() < num2.size())
	    return num2;
	else {
	    size_t i = 0;
	    while (i < num1.size()) {
	    	if (num1[i] < num2[i])
		    return num2;
		else if (num1[i] > num2[i])
	            return num1;
		else
	            i++;
	    }
	    return num1; // 
	}
}

vector<int>
getMaximumNumber(vector<int> num1, vector<int> num2, int k) {
	vector<int> ans_max;
	for (size_t i = 0; i <= k; i++) {
	    vector<int> ans1, ans2;
	    std::cout << "partition :" << i << ":" << k - i << std::endl;

	    //if (i <= num1.size()) {
	    // We should return any possible elements, even if k is greater than
	    // array size, because we again merge K elements, so results will be
	    // used from both arrays even if they are smaller
   	    ans1 = maximizeNumber(num1, i);
	    std::cout << "ans1.size :" << ans1.size() << std::endl;
	    std::cout << "ans1\n";
	    for (auto &v : ans1)
                std::cout << v << " ";
	    std::cout << std::endl;

	    ans2 = maximizeNumber(num2, k - i);
	    std::cout << "ans2.size :" << ans2.size() << std::endl;
	    std::cout << "ans2\n";
	    for (auto &v : ans2)
                std::cout << v << " ";
	    std::cout << std::endl;
	    //}

	    auto ans = maximizeNumberByMerge(ans1, ans2, k);
	    ans_max = compareVectors(ans_max, ans);
	    std::cout << " ans :" << ans.size()
	              << " a :" << ans1.size()
		      << " b :" << ans2.size() << std::endl;

	    std::cout << "result\n";
	    for (auto &v : ans)
                std::cout << v << " ";
	    std::cout << std::endl;

	    for (auto &v : ans_max)
		std::cout << v << " ";
	    std::cout << std::endl;
	}
	return ans_max;
}

int main(void) {
	//vector<int> nums { 9,2,1,1 };
	//vector<int> nums { 9,1,2,1 };
	//vector<int> nums { 1,0,1,0 };
	//vector<int> nums { 1,0 };
	//int k = 2;

	//vector<int> nums1 { 9,1,2,1 };
	//vector<int> nums2 { 9,1,2,1 };
	//int k = 2;
	//int k = 3;
	//int k = 4;
	//
	//vector<int> nums1 {3, 4, 6, 5};
	//vector<int> nums2 {9, 1, 2, 5, 8, 3};
	//int k = 5;

	//vector<int> nums2 {3, 4, 6, 5};
	//vector<int> nums1 {9, 1, 2, 5, 8, 3};
	//int k = 5;

	vector<int> nums1 {6, 7};
	vector<int> nums2 {6, 0, 4};
	int k = 5;

	//vector<int> nums1 {3, 9};
	//vector<int> nums2 {8, 9};
	//int k = 3;

	//vector<int> nums1 {8, 6, 9};
	//vector<int> nums2 {1, 7, 5};
	//int k = 3;
	//
	//vector<int> nums1 {2,5,6,4,4,0};
	//vector<int> nums2 {7,3,8,0,6,5,7,6,2};
	//int k = 15;

	std::cout << "nums1\n";
	for (auto &v : nums1)
	    std::cout << v << " ";
	std::cout << std::endl;

	std::cout << "nums2\n";
	for (auto &v : nums2)
	    std::cout << v << " ";
	std::cout << std::endl;

	std::cout << "knums1\n";
	auto ans1 = maximizeNumber(nums1, k);
	for (auto &v : ans1)
	    std::cout << v << " ";
	std::cout << std::endl;

	std::cout << "knums2\n";
	auto ans2 = maximizeNumber(nums2, k);
	for (auto &v : ans2)
	    std::cout << v << " ";
	std::cout << std::endl;

	std::cout << "result\n";
	auto ans = maximizeNumberByMerge(ans1, ans2, k);
	for (auto &v : ans)
	    std::cout << v << " ";
	std::cout << std::endl;

	std::cout << "result_final\n";
	auto ansf = getMaximumNumber(nums1, nums2, k);
	for (auto &v : ansf)
	    std::cout << v << " ";
	std::cout << std::endl;

	return 0;
}
