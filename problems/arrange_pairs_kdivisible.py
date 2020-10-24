#
# Check Pairs with K divisible sum
#
# Complexity :
#   +) O(KNlogN) : check for a range of possible sum
#
#   +) O(NlogN)  : reduce each element by remainder of K
# 
# https://leetcode.com/submissions/detail/412676789/

#TLE, o(KNLOGN)
def canArrangeI(arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: bool
        """
        counter = collections.Counter()
        s = 0
        for i in range(len(arr)):
            counter[arr[i]] = counter[arr[i]] + 1
            s = s + arr[i]
            
        if s % k != 0:
            return False
        
        sorted_arr = sorted(arr)
        lowerval = sorted_arr[0]  + sorted_arr[1]
        upperval = sorted_arr[-1] + sorted_arr[-2]
        kmin = lowerval / k
        kmax = upperval / k
        
        for p in counter:
            if counter[p] == 0:
                continue
            found = False
            counter[p] = counter[p] - 1
            for i in range(kmin, kmax + 1):
                q = i * k - p
                if q in counter and counter[q] > 0:
                    counter[q] = counter[q] - 1
                    found = True
                    break
            if found is False:
                return False
        return True
    
#O(NLOGN)
def canArrange(arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: bool
        """
        quick_sum = 0
        counter = collections.Counter()
        
        #use the fcat that we can use the remainder and check for sums of those pairs
        for i in range(len(arr)):
            rem = arr[i] % k
            counter[rem] = counter[rem] + 1
            quick_sum = quick_sum + arr[i] 
            
        # fast check : overall sum must be at least divisible    
        if quick_sum % k != 0:
            return False
                
        for p in counter:
            if counter[p] == 0:
                continue
            counter[p] = counter[p] - 1
            q = k - p
            if q in counter and counter[q] > 0:
                counter[q] = counter[q] - 1
            elif p is 0 and counter[p] > 0:
                counter[p] = counter[p] - 1
            else:
                print p,q
                return False
        return True
