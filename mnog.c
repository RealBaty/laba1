#include "mnog.h"

struct compl
{
    double real;
    double nreal;
};

struct elem
{
    void *k;
    int size,rsize;
};

void create_mnog(elem *a,int size)
{
    //a=(elem*)malloc(sizeof(elem));
    a->k=malloc(sizeof(compl)*size);
    a->size=size;
    a->rsize=size;
    for(int i=0;i<a->size;++i)
    {
        ((compl *)a->k)[i].real=0;
        ((compl *)a->k)[i].nreal=0;
    }
}

void create_zero(elem *a)
{
    a=(elem*)malloc(sizeof(elem));
    a->k=malloc(sizeof(compl)*16);
    a->size=0;
    a->rsize=16;
}

void delate_mnog(elem *a)
{
    free(a->k);
    free(a);
}

int empty(elem *a)
{
    if(a->size==0)
        return 1;
    return 0;
}

void resize(elem *a, int size)
{
    if(a->rsize>=size)
    {
        for(int i=a->size;i<size;++i)
        {
            ((compl *)a->k)[i].real=0;
            ((compl *)a->k)[i].nreal=0;
        }
        a->size=size;
    }
    else
    {
        void *t=a->k;
        a->k=malloc(sizeof(compl)*size);
        for(int i=0;i<a->size;++i)
            ((compl *)a->k)[i]=((compl *)t)[i];
        for(int i=a->size;i<size;++i)
        {
            ((compl *)a->k)[i].real=0;
            ((compl *)a->k)[i].nreal=0;
        }
        a->size=size;
        a->rsize=size;
        free(t);
    }
}

void reserve(elem *a, int size)
{
    if(size!=a->rsize)
    {
        void *t=malloc(sizeof(compl)*size);
        for(int i=0;i<size&&i<a->size;++i)
            ((compl *)t)[i]=((compl *)a->k)[i];
        free(a->k);
        a->k=t;
        a->rsize=size;
        if(size<a->size)
            a->size=size;
    }
}

void push (elem *a, compl x)
{
    if(a->rsize>a->size)
    {
        ((compl *)a->k)[a->size]=x;
        a->size++;
    }
    else
    {
        reserve(a,2*(a->rsize));
        ((compl *)a->k)[a->size]=x;
        a->size++;
    }
}

compl* getptr(elem *a)
{
    return (compl*)a->k;
}

compl get(elem *a,int x)
{
    if(x>a->size)
    {
        compl res;
        res.real=0;
        res.nreal=0;
        return res;
    }
    compl res=((compl *)a->k)[x];
    return res;
}

void insert(elem *a,int index,compl x)
{
    if(index<a->size)
    {
        ((compl *)a->k)[index]=x;
    }
    else
    {
        resize(a,index+1);
        ((compl *)a->k)[index]=x;
    }
}

elem* sum(elem *a,elem *b)
{
    elem *res=(elem*)malloc(sizeof(elem));
    if(a->size>b->size)
        create_mnog(res,a->size);
    else
        create_mnog(res,b->size);
    for(int i=0;i<a->size||i<b->size;++i)
    {
        getptr(res)[i].real=get(a,i).real+get(b,i).real;
        getptr(res)[i].nreal=get(a,i).nreal+get(b,i).nreal;
    }
    return res;

}

compl proiz(compl x,compl y)
{
    compl res;
    res.real=x.real*y.real-x.nreal*y.nreal;
    res.nreal=x.real*y.nreal+x.nreal*y.real;
    return res;
}

elem* scalar(compl x,elem *a)
{
    elem *res=(elem*)malloc(sizeof(elem));
   // printf("%f",get(a,10).nreal);
    create_mnog(res,a->size);
    for(int i=0;i<a->size;++i)
    {
        getptr(res)[i]=proiz(x,get(a,i));
    }
    //printf("%f",get(res,10).real);
    return res;
}

compl znach(compl x,elem *a)
{
    compl res;
    res.real=0;
    res.nreal=0;
    for(int i=0;i<a->size;++i)
    {
        compl t=get(a,i);
        for(int j=0;j<i;++j)
            t=proiz(t,x);
        res.nreal+=t.nreal;
        res.real+=t.real;
    }
    return res;
}


void map(elem *a,compl (*f)(compl))
{
    for(int i=0;i<a->size;++i)
    {
        getptr(a)[i]=(*f)(get(a,i));
    }
}

elem* pr(elem *x,elem *y)
{
    if(!empty(x)&&!empty(y))
    {
    elem *res=(elem *)malloc(sizeof(elem));
    create_mnog(res,x->size-1+y->size);
    for(int i=0;i<res->size;++i)
    {
        for(int j=0;j<=i;++j)
        {
            getptr(res)[i].real=get(res,i).real+proiz(get(x,j),get(y,i-j)).real;
            getptr(res)[i].nreal=get(res,i).nreal+proiz(get(x,j),get(y,i-j)).nreal;
        }
    }
    return res;
    }
    elem *res=(elem *)malloc(sizeof(elem));
    create_zero(res);
    return res;
}
