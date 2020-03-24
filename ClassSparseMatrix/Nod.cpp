#include "Nod.h"
#include <iostream>
using namespace std;


Nod::Nod()
{
    value = 0;
    lin = 0;
    col = 0;
    next = 0;
}

int Nod::getValue()
{
    return value;
}

int Nod::getCol()
{
    return col;
}

int Nod::getLin()
{
    return lin;
}

Nod* Nod::getNext()
{
    return next;
}


Nod::Nod(int v, int l, int c)
{
    value = v;
    lin = l;
    col = c;
    next = 0;
}

Nod::Nod(int v, int l, int c, Nod* n)
{
    value = v;
    lin = l;
    col = c;
    next = n;
}

void Nod::setValue(int x)
{
    value = x;
}

