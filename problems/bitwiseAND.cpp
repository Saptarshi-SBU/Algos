/*--------------------------------------------------------------------
 * Copyright (C) : 2017 Saptarshi Sen
 *
 * HackeRank Problem : https://www.hackerrank.com/challenges/30-bitwise-and
 *
 * Given set. Find two integers, and (where ), from set such that
 * the value of which is the maximum possible and also less than a
 * given integer. In this case, represents the bitwise AND operator.
 *
 * Constraint : k <= N
 *
 *  Solution A : O(k), Search for Pairs
 *      Iterate from k - 1 to 1;
        Set a 0 postition in i scanning left-right to see if a
        valid pair exists within N
        Fix : Equal to N
 *
 * Solution B : O(1), based on difference by 1-bit or many bit approach
 *      There exists a valid pair with product either k - 1 or k - 2,
 *      based on 1 bit difference between sucessive pairs or a pair
 *      if pair member < n;
 *
 *  g++ -std=c++11 bitwiseAND.cpp
 *-------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <cassert>
#include <stdlib.h>
#include <utility>
#include <fstream>

#define TEST(a, b) n = a; k = b;

using namespace std;

pair<int, int>
ListingI_GetPair(int n, int k) {
    for (int p = k - 1; p > 0; p--) {
       int bmask = 1 << 31;
       for (; bmask; bmask = bmask >> 1) {
          if (p & bmask)
             continue;
          // Got 0 position in p
          int ans = p | bmask;
          if (ans <= n)
             return pair<int, int>(p, ans);
       }
    }
    return pair<int, int>(0, 0);
}

int
ListingII_GetProduct(int n, int k) {
   int p = (k - 1);
   int bmask = 1;
   // Cases : pair within k; pair withtin n
   for (int b = 1; (p & bmask); bmask = bmask << 1, b++);
   int pmask = p | (bmask);
   return (n >= pmask) ? p : p - 1;
}

int ComputeMaxAND(int n, int k) {
#if 0
  auto p = ListingI_GetPair(n, k);
  return p.first & p.second;
#endif
  return ListingII_GetProduct(n, k);
}

int main(int argc, char **argv) {
    int n, k;
    pair<int, int> p;
#if 1
    TEST(5, 2)
    cout << "ans : " << ComputeMaxAND(n, k) << endl;
    TEST(8, 5)
    cout << "ans : " << ComputeMaxAND(n, k) << endl;
    TEST(2, 2)
    cout << "ans : " << ComputeMaxAND(n, k) << endl;
    TEST(127, 64)
    cout << "ans : " << ComputeMaxAND(n, k) << endl;
    TEST(123, 122)
    cout << "ans : " << ComputeMaxAND(n, k) << endl;
    TEST(712, 704)
    cout << "ans : " << ComputeMaxAND(n, k) << endl;
#else
    ifstream ifile("test.txt");
    while (ifile >> n >> k)
       cout << ComputeMaxAND(n, k) << endl;
#endif
    return 0;
}
