#
# Print all subsets or power set
#
# Algorithm : backtracking, O(2^N)
#
# https://leetcode.com/submissions/detail/398464567/
#
# I used dynamic programming using lists of lists and
# ran into werid issues. Stay away from lists and lists
# merging
#

import copy

# k : 1, iterate on arr with start pos : 0 : n - 1, 
# k : 2, iterate on arr
# k : 3, iterate on arr
def print_distinct_subsets(nums, k, p, subset, results):
    if k == 0:
        results.append(copy.copy(subset))
        return

    n = len(nums)
    if p >= n or k > n or k < 0:
        return

    for i in range(p, n):
        subset.append(nums[i])
        #print '==>subset :{} p :{} i :{} k :{}'.format(subset, p, i, k)
        print_distinct_subsets(nums, k - 1, i + 1, subset, results)
        subset.pop() #remove from back
        #print '<==subset :{} p :{} i :{} k :{}'.format(subset, p, i, k)

def print_all_distinct_subsets(nums):
    subset = []
    results = []
    for k in range(0, len(nums) + 1):
        print_distinct_subsets(nums, k, 0, subset, results)
    for i in results:
        print i
    print 'total subsets :{}'.format(len(results))

nums = [x for x in range(10)]
print_all_distinct_subsets(nums)
