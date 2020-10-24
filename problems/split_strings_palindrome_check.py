#
# Split Two Strings to Make Palindrome
#
# Complexity : O(N^2), O(N)
#
# Note : Palindromic String is composed of only prefix + suffix (not suffix + prefix)
#        After a partition, check the remainining substring in either a or b is itself a palindrome 
#
#        a...<palindrome>...
#                        ..a
#        a...
#           <palindrome>...a
#
#        a...
#           ...a
#
#        All the above three cases are possible
#
# Refs : https://leetcode.com/submissions/detail/412612705/

def checkPalindromeFormationUtil(a,b,i):
	s1 = a[:i] + "".join(b[i:])
	print "s1 :{}, {}".format(i, s1)
	return s1 == "".join(reversed(s1))

def checkPalindromeFormationI(a, b):
        """
        :type a: str
        :type b: str
        :rtype: bool
        """
        for i in range(len(a) + 1):
            if checkPalindromeFormationUtil(a,b,i) or checkPalindromeFormationUtil(b,a,i):
		#print i
                return True
        return False

def checkPalindromePartition(a ,b):
	l = 0
	r = len(b) - 1
	while l < r and a[l] == b[r]:
		l = l + 1
		r = r - 1
	if (l >= r):
		return True
	ar = a[l:r+ 1]
	br = b[l:r+ 1]
	return ar == "".join(reversed(ar)) or br == "".join(reversed(br))

def checkPalindromePartitioning(a,b):
	if a == "".join(reversed(a)):
		return True
	elif b == "".join(reversed(b)):
		return True
	else:
		return checkPalindromePartition(a,b)
        

def checkPalindromeFormationII(a, b):
	return checkPalindromePartitioning(a,b) or checkPalindromePartitioning(b,a)
'''
s1 = "123"
s2 = "321"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "123"
s2 = "111"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "12"
s2 = "12"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "1"
s2 = "2"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "11"
s2 = "22"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "abdef"
s2 = "fecab"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "ulacfd"
s2 = "jizalu"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "abdef"
s2 = "fecab"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "abd"
s2 = "bba"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1 = "abd"
s2 = "bbc"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)
'''
s1="pvhmupgqeltozftlmfjjde"
s2="yjgpzbezspnnpszebzmhvp"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)

s1="aejbaalflrmkswrydwdkdwdyrwskmrlfqizjezd"
s2="uvebspqckawkhbrtlqwblfwzfptanhiglaabjea"
print s1,s2, checkPalindromeFormationI(s1, s2)
print s1,s2, checkPalindromeFormationII(s1, s2)
