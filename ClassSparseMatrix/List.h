#ifndef LIST_H
#define LIST_H
#include "Nod.h"
#include "SparseMatrix.h"
#include <iostream>
using namespace std;

class Nod;
class SparseMatrix;
class List
{
    Nod * start, * last;
    int siz;

    public:
        List();
        List(const List &);
        void push(int, int, int);
        Nod * getStart();
        List & operator=(const List &);
        Nod * operator [](int);

        ~List();

    friend class SparseMatrix;
};

#endif
