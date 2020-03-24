#include "SparseMatrix.h"
#include "List.h"
#include "Nod.h"
#include <iostream>
using namespace std;

SparseMatrix::SparseMatrix()
{
    nrlin = 0; nrcol = 0;
    l = new List;
}

SparseMatrix::SparseMatrix(int n, int m)
{
    nrlin=n;
    nrcol=m;
    l=new List;
}

SparseMatrix::SparseMatrix(SparseMatrix & sm)
{
    nrlin = sm.nrlin;
    nrcol = sm.nrcol;
    l = new List(* sm.l);
}

SparseMatrix SparseMatrix::operator=(const SparseMatrix& sm)
{
    if (this != & sm){
      nrlin = sm.nrlin;
      nrcol = sm.nrcol;
      l = new List(* sm.l);
    }
    return *this;
}

int SparseMatrix::getLin()
{
    return nrlin;
}

int SparseMatrix::getCol()
{
    return nrcol;
}


SparseMatrix::~SparseMatrix()
{
    delete l;
}

istream & operator>>(istream & in,SparseMatrix & sm)
{
    int x;
    in >> sm.nrlin >> sm.nrcol;
    for (int i=0; i<sm.nrlin; i++)
        for (int j=0; j<sm.nrcol; j++)
    {
        in >> x; if (x) sm.l->push(x,i,j);
    }
    return in;
}

ostream & operator<<(ostream & out,const SparseMatrix & sm)
{
    Nod * n = sm.l -> getStart();
    for (int i=0; i<sm.nrlin; i++){
        for (int j=0; j<sm.nrcol; j++)
        {
            if (n && n->getLin()==i && n->getCol()==j){
                    out<<n->getValue()<<" ";
                    n = n->getNext();
            }
            else out<<0<<" ";
        }
        out<<endl;
   }
}

int * SparseMatrix::operator[](int index)const
{
    int * v = new int[nrcol];
    Nod * n = l -> getStart();
    int i = index;
    while(n && n->getLin()<index)
        {n = n -> getNext();}
    for (int j=0; j<nrcol; j++)
        {
            if (n && n->getLin()==i && n->getCol()==j){
                    v[j] = n->getValue();
                    n = n->getNext();
            }
            else v[j]=0;
        }
    return v;
}

SparseMatrix operator+(const SparseMatrix & sm1, const SparseMatrix & sm2)
{
    SparseMatrix sm;
    sm.nrcol=sm1.nrcol;
    sm.nrlin=sm1.nrlin;
    Nod * n1 = sm1.l->getStart();
    Nod * n2 = sm2.l->getStart();
    while ( n1 && n2 ){
        if (n1->getLin() < n2->getLin()){sm.l->push(n1->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
    }
        else if (n1->getLin() == n2->getLin() && n1->getCol() < n2->getCol()){sm.l->push(n1->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
    }
        else if (n1->getLin() == n2->getLin() && n1->getCol() == n2->getCol()){
           if (n1->getValue()+n2->getValue())
              sm.l->push(n1->getValue()+n2->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
              n2 = n2->getNext();
    }
        else {sm.l->push(n2->getValue(),n2->getLin(),n2->getCol());
              n2 = n2->getNext();
    }
    }
    while (n1){sm.l->push(n1->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
    }
    while (n2){sm.l->push(n2->getValue(),n2->getLin(),n2->getCol());
              n2 = n2->getNext();
    }
    return sm;

}

SparseMatrix operator-(const SparseMatrix & sm1, const SparseMatrix & sm2)
{
    SparseMatrix sm;
    sm.nrcol=sm1.nrcol;
    sm.nrlin=sm1.nrlin;
    Nod * n1 = sm1.l->getStart();
    Nod * n2 = sm2.l->getStart();
    while ( n1 && n2 ){
        if (n1->getLin() < n2->getLin()){sm.l->push(n1->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
    }
        else if (n1->getLin() == n2->getLin() && n1->getCol() < n2->getCol()){sm.l->push(n1->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
    }
        else if (n1->getLin() == n2->getLin() && n1->getCol() == n2->getCol()){
             if (n1->getValue()-n2->getValue())
              sm.l->push(n1->getValue()-n2->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
              n2 = n2->getNext();
    }
        else {sm.l->push((-1)*n2->getValue(),n2->getLin(),n2->getCol());
              n2 = n2->getNext();
    }
    }
    while (n1){sm.l->push(n1->getValue(),n1->getLin(),n1->getCol());
              n1 = n1->getNext();
    }
    while (n2){sm.l->push(n2->getValue(),n2->getLin(),n2->getCol());
              n2 = n2->getNext();
    }
    return sm;

}

SparseMatrix operator*(SparseMatrix sm1,SparseMatrix sm2)
{
    SparseMatrix sm(sm1.nrlin,sm2.nrcol);
    //cout<<sm.nrlin<<" "<<sm.nrcol;
    if (sm1.nrcol != sm2.nrlin) throw "nu merge";
    int *v;
    int x = sm1.nrcol;
    for ( int i=0; i<sm1.nrlin; i++ )
    {
       v = sm1[i];
       Nod * n2 = sm2.l->getStart();
       int x[sm1.nrcol];
       for ( int k=0; k<sm.nrcol; k++ ) x[k] = 0;
       for ( int j=0 ; j<sm2.nrcol; j++)
        {
           int ajutor = 0;
           while (n2){
            //cout<<n2->getLin()<<" ";
            x[n2->getCol()]+=n2->getValue()*v[n2->getLin()];
            n2=n2->getNext();
           }
        }
       for ( int k=0; k<sm2.nrcol; k++ ) if(x[k]) sm.l -> push(x[k],i,k);
    }
    return sm;
}

SparseMatrix  SparseMatrix::operator^(int x)
{
    if (this->nrcol != this->nrlin) throw "nu merge";
    x--;
    SparseMatrix sm=* this;
    //smaux=sm;
    while(x)
    {
        sm = sm * ( *this);
        x--;
    }
    return sm;
}

SparseMatrix operator*(SparseMatrix sm ,const int x)
{
    Nod * n2 = sm.l->getStart();
    while(n2){
        n2->setValue( n2->getValue() * x );
        n2=n2->getNext();
    }
    return sm;
}

SparseMatrix operator*(const int x, SparseMatrix sm)
{
    Nod * n2 = sm.l->getStart();
    while(n2){
        n2->setValue( n2->getValue() * x );
        n2=n2->getNext();
    }
    return sm;
}

bool SparseMatrix::operator==(const SparseMatrix& sm)
{
    Nod* n = sm.l->getStart();
    Nod* n2 = this->l->getStart();
    if (this->l->siz != sm.l->siz) return 0;
    while ( n && n2 ){
        if ( n->getValue() != n2->getValue() && n->getCol() != n2->getCol() && n->getLin() != n2->getLin() ) return 0;
        n=n->getNext();
        n2=n2->getNext();
        }
    return 1;
}


