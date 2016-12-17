/*-------------------------------------------------------------------------
 *
 * This is a program to count number of possible binary trees with elements.
 * The program counts for two different versions of the problem.
 * A)if elements are unlabelled. Means we cannot distinguish between the
 * elements. So the problem is reduced to structurally different binary
 * elements
 * Ans : T(N) = T(0)T(N-1) + T(1)T(N-2) + ... + T(N-1)T(0) = Catalan Number,
 * ((2n!)/((n+1)!*n!))
 * B)For labelled version, we need to include the number of possible
 * combinations with n elemens given a structure. So we just multiply
 * Ans : TL(N) = N!T(N)
 * C)For the number of BST, result is the same as the number of structurally
 * unique binary trees.
 *
 * Note : for deducing the above problem, we can start with 1 node, 2 nodes,
 * 3 nodes..and then build on.
 *
 * g++ -std=c++11 -o nr_bintree count_binary_trees.cpp
 *-------------------------------------------------------------------------*/

#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <limits>
#include <unistd.h>

using namespace std;

#define TEST_FACTORIAL 0
#define TEST_ALGO 1

#define OVERFLOW_BOUNDARY \
    numeric_limits<unsigned long long>::max()

#define CHECK_MUL_OVERFLOW(p, q) \
    (p > OVERFLOW_BOUNDARY/q)


inline uint64_t
factorial(uint32_t n) {
    if ((n == 0) || (n == 1))
        return 1;
    else {
        auto p = factorial(n - 1);
        if (CHECK_MUL_OVERFLOW(n, p))
            throw "Overflow in factorial!";
        return n * p;
    }
}

uint64_t
_unlabelled_CountBinaryTrees(uint32_t nr) {

    uint64_t result = 0;

    if ((nr == 0) || (nr == 1))
       return 1;

    for (int i = 0; i < nr; i++) {
       auto p = _unlabelled_CountBinaryTrees(i);
       auto q = _unlabelled_CountBinaryTrees(nr - i - 1);
       if (CHECK_MUL_OVERFLOW(p, q))
          throw "Overflow in Count!";
       result+=p*q;
    }
    return result;
}

uint64_t
_labelled_CountBinaryTrees(uint32_t nr) {

    uint64_t result = 0;
    auto f = factorial(nr);
    auto c = _unlabelled_CountBinaryTrees(nr);
    if (CHECK_MUL_OVERFLOW(f, c))
        throw "Overflow in Count!";
    return f*c;
}

int main(int argc, char **argv) {


   if (argc < 3) {
      cout << "Usage : program <min_nr_nodes> <max_nr_nodes>"
           << endl;
      return -1;
   }

   auto min_nr_nodes = atoi(argv[1]);
   auto max_nr_nodes = atoi(argv[2]);

#if TEST_FACTORIAL
   for (int i = min_nr_nodes; i < max_nr_nodes; i++)
       cout << factorial(i) << endl;
#endif

#if TEST_ALGO

   for (int i = min_nr_nodes; i <= max_nr_nodes; i++) {
       cout << i
            << ":"
            << "<nr_unlabelled>"
            << _unlabelled_CountBinaryTrees(i)
            << "<nr_labelled>"
            << _labelled_CountBinaryTrees(i)
            << endl;
   }
#endif

   return 0;
}

