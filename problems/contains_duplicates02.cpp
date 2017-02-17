/*-------------------------------------------------------------------
 * Copyright(C): 2017 Saptarshi Sen
 *
 * Contains Nearby Almost Duplicate Vector
 *
 * O(nlogk) : Use BST to maintain window and lower_bound trick
 *
 * https://leetcode.com/submissions/detail/93323450/
 *
 * -------------------------------------------------------------------*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <set>

using namespace std;

// Check dor d == 0 is for overflow conditions
// abs(2147483647 - (-1)) < 0
#define CHECK_LIMIT(d , t) (d >= 0 && d <= t)

void
PrintDebugString(multiset<int>& _set) {
    std::cout << "set: ";
    for (auto i : _set)
        std::cout << i << " ";
    std::cout << std::endl;
}

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {

   if (nums.empty() || (0 == k))
      return false;

   multiset<int> _set;

   int n = nums.size();
   k = std::min(k, n - 1);

   for (int i = 1; i <= k; i++)
      _set.insert(_set.end(), nums.at(i));

   for (int i = 0, j = k + 1; i < n; i++, j++) {

      if (_set.empty())
         break;

#if DEBUG
      PrintDebugString(_set);
#endif

      auto no = nums.at(i);
      int d  = 0;

      cout << no << ":" << endl;
      // Case 1:
      if (no <= *_set.begin()) {
         d = *_set.begin() - no;
         if (CHECK_LIMIT(d, t))
            return true;
      // Case 2:
      } else if (no >= *_set.rbegin()) {
         d = no - *_set.begin();
         if (CHECK_LIMIT(d, t))
            return true;
      // Case 3:
      } else  {
         // Note : lower_bound return 0 in case element not present
         // we can decrement iter to get to the next lowest as a trick
         // std::find_if returns last and not end in case no element found
         auto it = _set.lower_bound(no);
         d = abs(*it - no);
         if (CHECK_LIMIT(d, t))
            return true;

         if (it != _set.begin()) {
            it--;
            d = abs(*it - no);
            if (CHECK_LIMIT(d, t))
               return true;
         }
       }

      _set.erase(_set.find(nums.at(i + 1)));
      if (j < n)
         _set.insert(_set.end(), nums.at(j));
   }

   return false;
}

#define CPP_UNIT_TEST_DUP(func) \
    std::cout << ((func()) ? "PASS" : "FAIL") << std::endl;

#define CPP_UNIT_TEST_NODUP(func) \
    std::cout << ((func()) ? "FAIL" : "PASS") << std::endl;

bool test_001(void) {
    std::vector<int> v{1,2,3,4};
    return containsNearbyAlmostDuplicate(v, 3, 0);
}

bool test_002(void) {
    std::vector<int> v{1,2,3,1};
    return containsNearbyAlmostDuplicate(v, 3, 0);
}

bool test_003(void) {
    std::vector<int> v{1,2,3,4};
    return containsNearbyAlmostDuplicate(v, 1, 0);
}

bool test_004(void) {
    std::vector<int> v{1,2,3,1};
    return containsNearbyAlmostDuplicate(v, 2, 0);
}

bool test_005(void) {
    std::vector<int> v{1,2,3,1};
    return containsNearbyAlmostDuplicate(v, 6, 0);
}

bool test_006(void) {
    std::vector<int> v{0, 1, 2, 3, 2, 5};
    return containsNearbyAlmostDuplicate(v, 3, 0);
}

bool test_007(void) {
    std::vector<int> v{0, 1, 2, 4};
    return containsNearbyAlmostDuplicate(v, 3, 5);
}

bool test_008(void) {
    std::vector<int> v{0, 2, 4, 8};
    return containsNearbyAlmostDuplicate(v, 3, 1);
}

bool test_009(void) {
    std::vector<int> v{0, 2, 4, 8, 4};
    return containsNearbyAlmostDuplicate(v, 3, 1);
}

bool test_010(void) {
    std::vector<int> v{4, 1, 6, 3};
    return containsNearbyAlmostDuplicate(v, 100, 1);
}

bool test_011(void) {
    std::vector<int> v{-1, 2147483647};
    return containsNearbyAlmostDuplicate(v, 1, 2147483647);
}

bool test_012(void) {
    std::vector<int> v{2, 0, -2, 2};
    return containsNearbyAlmostDuplicate(v, 2, 1);
}

bool test_013(void) {
    std::vector<int> v{3, 6, 0, 4};
    return containsNearbyAlmostDuplicate(v, 2, 2);
}

int main(void) {
    CPP_UNIT_TEST_NODUP(test_001);
    CPP_UNIT_TEST_DUP(test_002);
    CPP_UNIT_TEST_NODUP(test_003);
    CPP_UNIT_TEST_NODUP(test_004);
    CPP_UNIT_TEST_DUP(test_005);
    CPP_UNIT_TEST_DUP(test_006);
    CPP_UNIT_TEST_DUP(test_007);
    CPP_UNIT_TEST_NODUP(test_008);
    CPP_UNIT_TEST_DUP(test_009);
    CPP_UNIT_TEST_DUP(test_010);
    CPP_UNIT_TEST_NODUP(test_011);
    CPP_UNIT_TEST_NODUP(test_012);
    CPP_UNIT_TEST_DUP(test_013);
    return 0;
}
