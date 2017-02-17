/*-----------------------------------------------------------------
 *
 * Copyright(C): 2017 Saptarshi Sen
 *
 * Determine duplicates within atmost k elements
 *
 * Implementation based on sliding window algorithm for the 
 * following STL containers
 *    +) Deque
 *    +) Set
 *
 * g++ -std=c++11 contains_duplicates.cpp -DDEBUG -g
 * ----------------------------------------------------------------*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <sstream>
#include <deque>
#include <set>

using namespace std;

std::string
ShortDebugString(deque<int>& dq) {
    std::ostringstream ss;
    for (auto i : dq)
        ss << i << " ";
    return ss.str();
}

std::string
ShortDebugString2(multiset<int>& dq) {
    std::ostringstream ss;
    for (auto i : dq)
        ss << i << " ";
    return ss.str();
}

// O(n2) : Deque provides simplest implementation
// for sliding window
bool UsingDeque(vector<int>& nums, int k) {

    deque<int> dq;

    const int n = nums.size();

    // init window
    for (int i = 1; i <= k; i++)
        dq.push_back(nums[i]);

    for (int i = 0, j = k + 1; i < n; i++, j++) {
#if DEBUG
        std::cout << ShortDebugString(dq) << std::endl;
#endif        
        if (dq.empty())
            break;

        // Check duplicate
        if (std::find(dq.begin(), dq.end(), nums.at(i)) != dq.end())
            return true;

        // decrease window
        dq.pop_front();

        // advance window
        if (j < n)
           dq.push_back(nums.at(j));
    }
    return false;
}

// O(nlogk) : Set offsers logarithmic complexity for
// searching duplicates
bool UsingSet(vector<int>& nums, int k) {

    // multiset version for holding duplicate entries
    multiset<int> _set;

    const int n = nums.size();

    // init window
    for (int i = 1; i <= k; i++)
        _set.insert(_set.begin(), nums[i]);

    for (int i = 0, j = k + 1; i < n; i++, j++) {
#if DEBUG
        std::cout << ShortDebugString2(_set) << std::endl;
#endif        
        if (_set.empty())
            break;

        // Check duplicate
        // Not free function stl::find is linear but set.find is sub-linear
        if (_set.find(nums.at(i)) != _set.end())
            return true;

        // decrease window
        _set.erase(std::find(_set.begin(), _set.end(), nums.at(i + 1)));

        // advance window
        if (j < n)
          _set.insert(_set.begin(), nums.at(j));
    }
    return false;
}

bool containsNearbyDuplicate(vector<int>& nums, int k) {

    const int n = nums.size();

    // Invalid Cases
    if ((n < 2) || (k == 0))
        return false;

    // In case k > n
    k = std::min(k, n - 1);

    //return UsingDeque(nums, k);
    return UsingSet(nums, k);

}

#define CPP_UNIT_TEST_DUP(func) \
    std::cout << ((func()) ? "PASS" : "FAIL") << std::endl;

#define CPP_UNIT_TEST_NODUP(func) \
    std::cout << ((func()) ? "FAIL" : "PASS") << std::endl;

bool test_001(void) {
    std::vector<int> v{1,2,3,4};
    return containsNearbyDuplicate(v, 3);
}

bool test_002(void) {
    std::vector<int> v{1,2,3,1};
    return containsNearbyDuplicate(v, 3);
}

bool test_003(void) {
    std::vector<int> v{1,2,3,4};
    return containsNearbyDuplicate(v, 1);
}

bool test_004(void) {
    std::vector<int> v{1,2,3,1};
    return containsNearbyDuplicate(v, 2);
}

bool test_005(void) {
    std::vector<int> v{1,2,3,1};
    return containsNearbyDuplicate(v, 6);
}

bool test_006(void) {
    std::vector<int> v{0, 1, 2, 3, 2, 5};
    return containsNearbyDuplicate(v, 3);
}

int main(void) {
    CPP_UNIT_TEST_NODUP(test_001);
    CPP_UNIT_TEST_DUP(test_002);
    CPP_UNIT_TEST_NODUP(test_003);
    CPP_UNIT_TEST_NODUP(test_004);
    CPP_UNIT_TEST_DUP(test_005);
    CPP_UNIT_TEST_DUP(test_006);
    return 0;
}

