#include <stdio.h>
#include <stdlib.h>
#include "mnog.h"

struct compl
{
    double real;
    double nreal;
};

struct elem
{
    compl *k;
    int size,rsize;
};

int main()
{
    elem a,c;
    create_mnog(&a,5);
    create_mnog(&c,5);
    compl b;
    b.real=0;
    b.nreal=5;
    insert(&a,10,b);
    elem *n=scalar(b,&a);
    printf("%f",znach(b,n).real);
    //printf("%f",proiz(proiz(b,b),b).nreal);
    return 0;
}
