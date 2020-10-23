#
# Random number generation from an existing random API
#
# Avg Case: O(1), Worst Case: O(inf)
#

def rand10(self):
        """
        :rtype: int
        """
        #The idea is how to generate a rand10 version number naturally by
        #rolling dice with rand7. Basically use iteratons and folding.
        
        #Algorithm
        #Rand 7 Results in a number between 1 to 7
        #If you run rand 7() twice. It will result in the probability of returning an 
        #integer between 1 and 49. Now if we mod this result by 10 it won’t be uniform.
        #But if the number is less than=40. Then it will be uniform for rand 10().
        #Because the number then forms a part of rand() 10. If the resulting number is 
        #greater than 40. You have to run it again. until the number comes between 1
        #and 40. The worst case is O(infinity). But the probability of this happening is
	#astronomically small.
        p = 0
        while True:
	    #the formulation is choosing co-ordinate from a 7x7 matrix, which
	    #should keep the distribution uniform
            x, y = rand7(), rand7()
            #make sure, we see numbers from 1 onwards for use (x-1)
            p = (x - 1)* 7 + y
            if p <= 40:
                break
        #folding        
        return (p % 10) + 1        
        
