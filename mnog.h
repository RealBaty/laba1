#ifndef MNOG_H_INCLUDED
#define MNOG_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct compl compl;

typedef struct elem elem;

void create_mnog(elem *a,int size);

void create_zero(elem *a);

void delate_mnog(elem *a);

int empty(elem *a);

void resize(elem *a,int size);

void reserve (elem *a,int size);

void push(elem *a,compl x);

compl* getptr(elem *a);

compl get(elem *a, int x);

void insert (elem *a,int index,compl x);

elem* sum(elem *a,elem *b);

elem* scalar(compl x,elem *a);

compl proiz(compl x,compl y);

compl znach(compl x, elem *a);

void map(elem *a,compl (*f)(compl));

elem* pr(elem *x,elem *y);

#endif // MNOG_H_INCLUDED
