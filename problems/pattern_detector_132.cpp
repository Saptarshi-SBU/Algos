/*
 * Find a Subsequence pattern in an array
 *
 * O(n^2) solution because of linear iterators associated with STL set.
 * Otherwise, this could have been a O(NlogN) approach
 *
 * The idea is to keep two sub-trees and use them to check the constraint
 * while the array is traversed.
 * https://leetcode.com/submissions/detail/410744785/
 *
 */
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(void) {
	std::set<int> sub_left, sub_right;
	std::map<int, int> map_right;

	//std::vector<int> v{100,2,1,-1,6,2,3,210};
	//std::vector<int> v{1,2,2,3,210};
	//std::vector<int> v{1,1,2,3,2};
	//std::vector<int> v{1,1,2,3,2};
	//std::vector<int> v{1,1,2};
	//std::vector<int> v{1,2};
	//std::vector<int> v{1,2,3,2,1};
	std::vector<int> v{2,1,3,4};

	for (size_t i = 0; i < v.size(); i++) {
		sub_right.insert(v.at(i));
		if (map_right.find(v.at(i)) == map_right.end())
			map_right[v.at(i)] = 0;
		map_right[v.at(i)]++;
	}

	// Note : I missed to remove the 0th index from the right sub_tree
	for (size_t i = 0; i < v.size() - 1; i++) {
		map_right[v.at(i)]--;
		if (map_right[v.at(i)] == 0)
			sub_right.erase(v.at(i));
		if (i == 0)
			continue;
		sub_left.insert(v.at(i - 1));
		auto it_left = sub_left.begin();
		// middle should be greater than the smallest element in the left subtree
		if (v.at(i) < *it_left)
			continue;
		// right subtree should have an element greater than the smaller element
		// in the left subtree but less than the middle element
		auto it_right = std::upper_bound(sub_right.begin(), sub_right.end(), *it_left);
		if (it_right == sub_right.end())
			continue;
		//std::cout << "dbg: " << i << " left:" << *it_left
		//          << " mid:" << v.at(i) << " right:" << *it_right << std::endl;
		while (it_right != sub_right.end()) {
			if (*it_right < v.at(i)) {
				std::cout << *it_left << ":" << v.at(i)
					  << ":" << *it_right << std::endl;
				return true;
			}
			it_right++;
		}
	}
	return false;
}
