#
# Find Smallest Missing Positive Number
#
# Complexity : O(NlogN)
#
# Boundary Cases to look for :
# a) zero or negative numbers
# b) repeated numbers
# c) empty array
#
# https://leetcode.com/submissions/detail/412426116/

def firstMissingPositive(nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums = sorted(nums)
        p = 0
        q = 0
	prev = None
        while p < len(nums):
	    #positive numbers
            if nums[p] > 0:
		# increment q keeping in mind that there can be duplicate entries
		# we cannot incrementq based on every index we scan
		if prev:
			#probe for the next missing number
			if prev != nums[p]:
				q = q + 1
            			if q != nums[p]:
                			return q
		else:
			#probe for the next missing number
			q = q + 1
            		if q != nums[p]:
                		return q
			#we do not increment q here but in next iter based on next index lookup
	    prev = nums[p]
            p = p + 1
           
	#if we reach here means that there are no possible missing element in the array found till now
        return q + 1

nums = [ 1,2,3,4 ]
print firstMissingPositive(nums)

nums = [ 1,2,4,5 ]
print firstMissingPositive(nums)

nums = [ 2,4,5 ]
print firstMissingPositive(nums)

nums = [ 1,2,0 ]
print firstMissingPositive(nums)

nums = [0,2,2,1,1]
print firstMissingPositive(nums)

nums = [1,2,2,1,3,1,0,4,0]
print firstMissingPositive(nums)
