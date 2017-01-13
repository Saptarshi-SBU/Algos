/*-------------------------------------------------------------------
 *
 * Generate Parenthesis
 *
 * Given n pairs of parentheses, write a function to generate all 
 * combinations of well-formed parentheses.
 *
 * https://leetcode.com/submissions/detail/89016756/
 *
 * Result:
 *
 * 1
 * Total No of valid combinations 1
 * 2
 * Total No of valid combinations 2
 * 3
 * Total No of valid combinations 5
 * 4
 * Total No of valid combinations 14
 * 5
 * Total No of valid combinations 42
 * 6
 * Total No of valid combinations 132
 * 7
 * Total No of valid combinations 429
 * 8
 * Total No of valid combinations 1430
 * 9
 * Total No of valid combinations 4862
 * 10
 * Total No of valid combinations 16796
 * 11
 * Total No of valid combinations 58786
 * 12
 * Total No of valid combinations 208012
 * 13
 * Total No of valid combinations 742900
 * 14
 * Total No of valid combinations 2674440
 * 15
 * Total No of valid combinations 9694845
 * 16
 * Total No of valid combinations 35357670
 * 17
 * Total No of valid combinations 129644790
 *
 *  Note : Because of recursion, memory consumption fairly increases
 *  with n. typical figure, for n = 18, cpu ~ 1%, mem ~ 80%
 *  TBD: Think of an iterative way to the problem 
 * -----------------------------------------------------------------*/

#include<iostream>
#include<string>
#include<vector>
#include <unistd.h>

using namespace std;

void 
_generateParenthesis(int p, int q, string str, vector<string> &v) {

    // (p > q) check ensures that all
    // combinations are legal formations
    if ((p < 0) || (p > q))
       return;

    if ((p == 0) && (q == 0)) {
       v.push_back(str);
    }  else {
       _generateParenthesis(p - 1, q, string(str).append("("), v);
       _generateParenthesis(p, q - 1, string(str).append(")"), v);  
    }

    return;
}

vector<string> 
generateParenthesis(int n) {

    string str;
    vector<string> result;

    if (n)
       _generateParenthesis(n, n, str, result); 

    return result;
}    

int main(int argc, char**argv) {

     int n = -1;

     bool print = false;

     if (argc < 3) {
         cout << "Usage :  -n <num pairs> -p <print>" << endl;
         return -1;
     }    

     char c;

     while ((c = getopt (argc, argv, "n:p")) != -1) {
        switch (c) {
           case 'n' :
               n = atoi(optarg);
               break;
           case 'p' :
               print = true;
               break;
           default:
               break;
        }       
    }

    if (n < 0) {
        cout << "Invalid argument" << endl;
        return -1;
    }    

    auto result = generateParenthesis(n);

    if (print) {
        unsigned long int i = 1;
        for (auto it = result.begin(); it != result.end(); it++, i++)
           cout << i << ":" << *it << endl;
    }    

    cout << "Total No of valid combinations " << result.size() << endl;
    return 0;
}
