#
# Find Kth Missing Positive Number
#
# O(NlogN) foe constructing and look-up tree
#
def findKthPositiveBUG(arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: int
        """
        #[] : K
        #[0,1,3] : K(1) : 2, K(2):4
        #[0,1,1,2,5] : K(1) : 3
        p = 0
        n = 0
        i = 0
        prev = None
        while i < len(arr):
            if arr[i] > 0:
                if prev:
                    if prev != arr[i]:
		    	#BUG Case: one in updated may already have been seen	
                        p = p + 1
                        #missing element
                        if p != arr[i]:
                            n = n + 1
                            if n == k:
                                return p
                else:
                    p = p + 1
                    if p != arr[i]:
                        n = n + 1
                        if n == k:
                            return p
            prev = arr[i]
            i = i + 1
        
        for i in range(n + 1, k + 1):
            p = p + 1
        return p

def findKthPositive(arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: int
        """
	s = set()
	for i in range(len(arr)):
		if arr[i] >= 0:
			s.add(arr[i])
	i = 0
	n = 0
	while n < k :
		i = i + 1
		if i not in s:
			n = n + 1
	return i

nums = [ 1,2,3,4 ]
print nums
for i in range(1, 6 + 1):
	print i, findKthPositive(nums,i)

nums = [ 0,1,2,2,4,7 ]
print nums
for i in range(1, 4 + 1):
	print i, findKthPositive(nums,i)
