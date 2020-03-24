#include <iostream>
#include <fstream>
#include <assert.h>
#include "SparseMatrix.h"

using namespace std;
ifstream f("SparseMatrix.txt");
ifstream g("asserttest.txt");

void haisanucrape()
{
    SparseMatrix sm(3,3);
    assert((*sm.l)[0]==0);
    assert(sm.getCol()==3);
    assert(sm.getLin()==3);
    sm.l->push(1,0,0);
    sm.l->push(3,0,2);
    sm.l->push(3,1,1);
    sm.l->push(1,1,2);
    sm.l->push(6,2,0);
    sm.l->push(1,2,2);
    SparseMatrix sm2;
    g>>sm2;
    assert(sm2 == sm);
    sm2 = sm + sm;
    assert(sm2==sm+sm);
    sm2 = sm2 - sm;
    assert(sm2==sm);
    SparseMatrix smtest;
    g >> smtest;
    assert(smtest==sm*sm);
    assert(smtest==(sm^2));
    SparseMatrix x = sm; assert(x == sm);
    SparseMatrix smtest2; g >> smtest2;
    assert( smtest2 == 79*sm );
    assert( smtest2 == sm*79 );
}

int main()
{
   haisanucrape();
}
