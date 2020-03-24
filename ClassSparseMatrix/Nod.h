#ifndef NOD_H
#define NOD_H
#include "List.h"
#include "SparseMatrix.h"
#include <iostream>
using namespace std;


class Nod
{
    int value;
    int col;
    int lin;
    Nod * next;

    public:
        Nod();
        Nod(int, int, int);
        int getValue();
        int getCol();
        int getLin();
        void setValue( int );
        Nod * getNext();
        Nod(int, int, int, Nod*);

    friend class List;
    friend class SparseMatrix;
};

#endif
