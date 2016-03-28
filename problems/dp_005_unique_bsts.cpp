/*-------------------------------------------------------------------------------------------
 *
 * Unique BSTs
 *
 * -----------------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {

    

    int *p;

    

    int numTreesUtil(int lo, int high) {

     

        int sum = 0;

        

        if (lo == high)

            return 1;

        else 

        if (lo > high)

            return 0;

        else {    

            for (int i = lo; i <= high; i++)

                sum+=(numTreesUtil(lo, i - 1) + numTreesUtil(i + 1, high));

        }

        return sum;

    }

    int numTreesUtil2(int lo, int high, int *p) {

        int sum = 0;

        

        if (lo == high)

            return 1;

        else 

        if (lo > high)

            return 0;

        else {    

            for (int i = lo; i <= high; i++) {

                int m = i - 1 - lo;

                if (m > 0) {

                    if (!p[m])

                        p[m] = numTreesUtil2(lo, i - 1, p);

                }    

                int n = high - i - 1;    

                if (n > 0) {

                    if(!p[n]) 

                        p[n] = numTreesUtil2(i + 1, high, p);    

                }    

		if ((m >= 0) && (n >= 0))
			sum+=(p[m] * p[n]);
		else if (m >= 0)
			sum+=p[m];
		else if (n >= 0)
			sum+=p[n];
            }

        }

        return sum;

    }

    

public:

/*

    int numTrees(int n) {

        if (0 == n)

            return 1;

        else

        if (n > 0)    

            return numTreesUtil(1, n);

        else

        if (n < 0)

            return numTreesUtil(n, 1);

    }

*/  

    int numTrees(int n) {

        if (0 == n)

          return 1;

        

        p = new int[n];

        p[0] = 1;

        return numTreesUtil2(1, n , p);

    }

	// optimal version : Bottom-Up : computes for smaller nodes ; and then up
    int numTrees2(int n) {
	int  ans = 0;
	int *p = 0;

	if (0 == n)
		return 1;

	p = new int[n + 1];
	p[0] = 1;
	p[1] = 1;

	for(int i = 2; i <= n; i++) 
		for (int j = 0; j < i; j++) 
			p[i] = p[i] + p[j]*p[i - j - 1];	

	ans = p[n];
	delete [] p;
	return ans;
    }	

    void showp(int n) {

	for (int i = 0; i < n; i++)
		cout << p[i] << " ";
	cout << endl;
   }	  

};

int main(void) {
	const int n = 7;
	Solution *sol = new Solution;
	cout << sol->numTrees(n) << endl;
	cout << sol->numTrees2(n) << endl;
	//sol->showp(n);
	return 0;
}


