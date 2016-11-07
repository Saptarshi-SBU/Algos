/*-------------------------------------------------------
 * A Matrix Template library
 *
 *
 * -----------------------------------------------------*/
#ifndef _MATRIX_H
#define _MATRIX_H

#include<vector>
#include<iostream>
#include <stdexcept>

using namespace std;

template<class T>
class matrix {

    private: 
         vector<T> elements;
    public:
         const unsigned rows;
         const unsigned cols;
    protected:
         void range_check(unsigned i, unsigned j) const {
             if (rows <= i)
                 throw range_error("matrix access out of range");
             else if (cols <= j)
                 throw range_error("matrix access out of range");
         }
         
     public:  
         T& operator()(unsigned i, unsigned j) {
            range_check(i, j);
            return elements[i*cols + j];
         }
        
         const T& operator()(unsigned i, unsigned j) const {
            range_check(i, j);
            return elements[i*cols + j];
         }

         matrix(unsigned rows, unsigned cols, T*elements = 0):
             rows(rows), cols(cols), elements(rows*cols, T(0)) {
             if ((0 == rows) || (0 == cols)) 
                 throw range_error("attempt to create a degenrate matrix");
         }

         matrix(const matrix<T>& cp) : rows(cp.rows), cols(cp.cols), elements(cp.elements) {
         }
      
         ~matrix() {
         }

         matrix<T>& operator=(const matrix<T>& cp) {
             if ((rows != cp.rows) || (cols != cp.cols))
                 throw domain_error("matrix not of same order");
             for (int i = 0; i < rows*cols; i++)
                 elements[i] = cp.elements[i];
             return (*this); 
         }

         bool operator==(const matrix<T>& cp) const {
             if ((rows != cp.rows) || (cols != cp.cols))
                 return false;
             for (int i = 0;i < rows*cols; i++) 
                 if (elements[i] != cp.elements[i])
                     return false;  
             return true;
         }

         matrix<T>& operator+=(const T&a) {
             for (int i = 0;i < rows*cols; i++)
                 elements[i]+=a;
             return (*this); 
         }

         matrix<T> operator+=(const T&a) const {
             return matrix<T>(*this).operator+=(a);
         }

         matrix<T>& operator*=(const T&a) {
             for (int i = 0;i < rows*cols; i++)
                 elements[i]*=a;
             return (*this); 
         }

         matrix<T> operator*=(const T&a) const {
             return matrix<T>(*this).operator*=(a);
         }
         
         matrix<T>& operator/=(const T&a) {
             for (int i = 0;i < rows*cols; i++)
                 elements[i]*=a;
             return (*this); 
         }

         matrix<T> operator/=(const T&a) const {
             return matrix<T>(*this).operator/=(a);
         }
};        

template<class T>
ostream& operator<<(ostream& o, const matrix<T>& M) {
    o << endl;
    for(int i=0;i<M.rows;i++) {
        o << "[ ";
        for(int j=0;j<M.cols;j++)
            o << M(i,j) << " ";
            o << "]" << endl;
        }
    o << endl;
    return o;
}

template<class T>
matrix<T> transpose(matrix<T>& M) {
    matrix<T> MT(M.cols, M.rows);
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            MT(j, i) = M(i, j);
        }
    }
    return MT;
}

template<class T>
void transpose_square(matrix<T>& M) {
    if (M.cols != M.rows) 
        throw domain_error("Not a Square Matrix");
  
    for (int i = 0; i < M.rows; i++) {
        for (int j = 0; j < M.cols; j++) {
            auto temp = M(j, i);
            M(j, i) = M(i, j);
            M(i, j) = temp;
        }
    }
}

template<class T>
void reverse(matrix<T>& M) {
    for (int i = 0; i < M.rows; i++) {
        int p = 0;
        int q = M.cols - 1;
        while (p < q) { 
            auto temp = M(i, p);
            M(i, p) = M(i, q);
            M(i, q) = temp;
            p++;
            q--;
        }
    }
}

#endif 
