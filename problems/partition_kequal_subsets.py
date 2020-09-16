#
# Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into k
# non-empty subsets whose sums are all equal.
#
# Example 1:
#
# Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
# Output: True
# Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
#   
# Note:
#
# 1 <= k <= len(nums) <= 16.
# 0 < nums[i] < 10000.
#

import unittest

def canPartitionKSubsetsBackTracking(nums, k, ksum, curr_sum, visited):
    #ksub-sets partitions created
    if k == 0:
        return True

    #we are exhausted and yet have not completed all sub-sets
    if len(visited) == len(nums):
        return False

    for i in range(len(nums)):
        # index not in any bucket
        if i not in visited:
            visited.add(i)
            if curr_sum > nums[i]:
                if canPartitionKSubsetsBackTracking(nums, k, ksum, curr_sum - nums[i], visited) is True:
                    return True
            elif curr_sum == nums[i]:
                if canPartitionKSubsetsBackTracking(nums, k - 1, ksum, ksum, visited) is True:
                    return True
            visited.remove(i);
    return False
    
def canPartitionKSubsets(nums, k):
    net = sum(nums)
    ksum, r = divmod(net, k)
    if r != 0:
        return False
    visited = set()
    return canPartitionKSubsetsBackTracking(nums, k, ksum, ksum, visited)

class Tests(unittest.TestCase):

    def test_01(self):
            nums = [4, 3, 2, 3, 5, 2, 1]
            k = 4
            self.assertEqual(canPartitionKSubsets(nums, k), True)
         
    def test_02(self):
            nums = [4, 3, 2, 3, 5, 2]
            k = 4
            self.assertEqual(canPartitionKSubsets(nums, k), False)

    def test_03(self):
            nums = [4, 3, 3, 3, 5, 2]
            k = 2
            self.assertEqual(canPartitionKSubsets(nums, k), True)

    def test_04(self):
            nums = [4, 2, 3, 6, 3, 1, 5]
            k = 3
            self.assertEqual(canPartitionKSubsets(nums, k), True)

if __name__ == "__main__":
    unittest.main()
