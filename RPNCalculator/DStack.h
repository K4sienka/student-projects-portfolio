#ifndef _DSTACK_H_
#define _DSTACK_H_


typedef struct tagStackDItem
{
  double          key;
  tagStackDItem* pNext;

}StackDItem;

StackDItem* createDStack();


void    Dpush( StackDItem** pDStack , double x  );      // wloz na stos
double  Dpop( StackDItem** pDStack );                   // zdejmij i zwroc szczytowy elem stosu
double  Dtop( StackDItem* pDStack );                    // zwroc szczytowy elem stosu
void    Ddel( StackDItem** pDStack );                   // usun szczytowy (zdejmij)
int     DisEmpty( StackDItem* pDStack );                // zwraca true jesli stos pusty - else false

#endif