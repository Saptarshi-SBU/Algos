#
# Minimum Insertions to Form Palindrome
#
# O (2^N)
#
# Find the minimum number of insertions in the substring str[l+1,…….h].
# Find the minimum number of insertions in the substring str[l…….h-1].
# Find the minimum number of insertions in the substring str[l+1……h-1].
#
#https://leetcode.com/submissions/detail/412763868/

# incorrect
# order of insertion matters in computing minimum length
# abad
# (d)abad vs abad(a)
def minInsertionsI( s):
        """
        :type s: str
        :rtype: int
        """
        l = 0
        r = len(s) - 1
        c = 0
        while l <= r:
                if s[l] == s[r]:
                        l = l + 1
                        r = r - 1
                else:
                        #insert to equalize l and r
                        c = c + 1
                        l = l + 1
        return c
    
# incorrect
#center based expansion also missed multiple orders of insertion
def countInsertionsOdd( s, p):
        i = p - 1
        j = p + 1
        c = 0
        while i >= 0 and j < len(s):
            if s[i] != s[j]:
                c = c + 1
                i = i - 1
            else:
                i = i - 1
                j = j + 1
        return c        
      
# incorrect
def countInsertionsEven( s, p, q):
        i = p
        j = q
        c = 0
        while i >= 0 and j < len(s):
            if s[i] != s[j]:
                c = c + 1
                i = i - 1
            else:
                i = i - 1
                j = j + 1
        return c     
    
# incorrect
def minInsertionsII( s):
        c = len(s)
        for i in range(len(s)):
            c_odd = countInsertionsOdd(s, i)
            c = min(c, c_odd)
            if i > 0:
                c_evn = countInsertionsEven(s, i, i - 1)
                c = min(c, c_evn)
        return c
    
# recursion based which considers all possible orders
def countInsertionsI( s, p, q):
        if p > q:
            return 0
        
        if s[p] == s[q]:
            return countInsertions(s, p + 1, q - 1)
        else:
            return min(1 + countInsertions(s, p + 1, q), \
                       1 + countInsertions(s, p, q - 1))
        
def minInsertionsIII( s):
        return countInsertionsI(s, 0 , len(s) - 1)
    
#using memoization
def countInsertions( s, p, q, dp):
        if p > q:
            return 0
        elif s[p] == s[q]:
            if dp[p][q] < 0:
                dp[p][q] = countInsertions(s, p + 1, q - 1, dp)
            return dp[p][q]
        else:
            if dp[p + 1][q] < 0:
                    dp[p + 1][q] = countInsertions(s, p + 1, q, dp)
            if dp[p][q - 1] < 0:
                    dp[p][q - 1] = countInsertions(s, p, q - 1, dp)
            dp[p][q] = min(1 + dp[p + 1][q], 1 + dp[p][q - 1])
            return dp[p][q]

def minInsertions( s):
        dp = [ [] for x in range(len(s)) ]
        for i in range(len(dp)):
                dp[i] = [ -1 for x in range(len(s)) ]
        return countInsertions(s, 0 , len(s) - 1, dp)

s = "ab"
print s
print minInsertions(s)

s = "abc"
print s
print minInsertions(s)

s = "abccb"
print s
print minInsertions(s)

s = "aa"
print s
print minInsertions(s)

s = "zjveiivwc"
print s
print minInsertions(s)

s = "zjveiiwvc"
print s
print minInsertions(s)
