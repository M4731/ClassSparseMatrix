#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include "List.h"
#include <iostream>
using namespace std;

class List;
class SparseMatrix
{
    List * l;
    int nrcol;
    int nrlin;

    public:
        SparseMatrix();
        SparseMatrix(SparseMatrix &);
        SparseMatrix(int, int);
        int getLin();
        int getCol();
        friend istream & operator>>(istream & ,SparseMatrix &);
        friend ostream & operator<<(ostream & ,const SparseMatrix &);
        int * operator[](int)const;
        friend SparseMatrix operator+(const SparseMatrix &,const SparseMatrix &);
        friend SparseMatrix operator-(const SparseMatrix &,const SparseMatrix &);
        friend SparseMatrix operator*(SparseMatrix ,SparseMatrix );
        SparseMatrix operator^(int );
        SparseMatrix operator=(const SparseMatrix &);

        friend SparseMatrix operator*(SparseMatrix ,const int);
        friend SparseMatrix operator*(const int, SparseMatrix);

        bool operator==(const SparseMatrix&);

        ~SparseMatrix();
        friend void haisanucrape();

};

#endif
