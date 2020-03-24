#include "List.h"
#include "Nod.h"
#include <iostream>
using namespace std;


List::List()
{
     start = 0;
     last = 0;
     siz = 0;
}

List::List(const List & l)
{
     start = 0;
     last = 0;
     siz = 0;
     Nod * n = l.start;
     while (n){
        this->push(n->value, n->lin, n->col);
        n=n->next;
     }
}

void List::push(int v, int l, int c)
{
    Nod * n = new Nod(v, l, c);
    if (siz){
       last -> next = n;
       last = n;
    }
    else{
        start = last = n;
    }
    siz++;
}

Nod* List::getStart()
{
    return start;
}

List::~List()
{
    if (siz) {
        Nod * n = start->getNext();
        Nod * prev = start;
        while(n){delete prev;
                 prev = n;
                 n = n->getNext();}
        delete prev;
    }
}

List& List::operator=(const List& lista)
{
     List l;
     Nod * n = lista.start;
     while (n){
        l.push(n->value, n->lin, n->col);
        n=n->next;
     }
}

Nod* List::operator[](int i)
{
    Nod * n =  this->start;
    while (i)
    {
        n = n->next;
        i--;
    }
    return n;
}


