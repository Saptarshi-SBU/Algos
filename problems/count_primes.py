# prime number counting
# ref ://www.geeksforgeeks.org/how-is-the-time-complexity-of-sieve-of-eratosthenes-is-nloglogn/ https://leetcode.com/submissions/detail/400785293/u
#

#Sieve of Erasthanus
#O(n(log(log(n))))
def countPrimes(n):
    """
    :type n: int
    :rtype: int
    """
    c = 0
    pl = [True] * (n + 1)
    for i in range(2, n):
        if not pl[i]:
            continue
        else:
            c = c + 1
            k = 1
            while (i * k) < n:
                pl[i * k] = False
                k = k + 1
    return c
    
def countPrimesIII(n):
    """
    :type n: int
    :rtype: int
    """
    c = 0
    pl = [True] * (n + 1)
    for i in range(2, n):
        if not pl[i]:
            continue
        else:
            p = True
            for j in range(2, int(math.sqrt(i)) + 1):
                if i % j == 0:
                    p = False
                    break
            if p:
                c = c + 1
                k = 1
                while (i * k) < n:
                    pl[i * k] = False
                    k = k + 1
    return c                
    
#O(n(sqrt(n)))
def countPrimesII(n):
    """
    :type n: int
    :rtype: int
    """
    # Note : 1 is not a prime number
    c = 0
    for i in range(2, n):
        no_prime = True
        for j in range(2, int(math.sqrt(i)) + 1):
            if i % j == 0:
                no_prime = False
                break
        if no_prime:
            c = c + 1
    return c
    
#O(n^2)
def countPrimesI(n):
    """
    :type n: int
    :rtype: int
    """
    # Note : 1 is not a prime number
    c = 0
    for i in range(2, n):
        no_prime = True
        for j in range(2, i):
            if i % j == 0:
                no_prime = False
                break
        if no_prime:
            c = c + 1
    return c

if __name__ == "__main__":
    print countPrimes(100000)
