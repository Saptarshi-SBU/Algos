/*------------------------------------
 * Program to rotate a matrix by 90
 * using matrix template library
 *
 * g++ -g -o matrix -std=c++11 matrix_rotate.cpp
 * ----------------------------------*/

#include "matrix.h"

void rotateby90(matrix<int>& m) {
    auto n = transpose(m);
    reverse(n);
}

void rotateby90square(matrix<int>& m) {
    transpose(m);
    reverse(m);
}

int main(void) {
    matrix<int> m(1000,1000);
    rotateby90(m);
    rotateby90square(m);
    return 0;
}
