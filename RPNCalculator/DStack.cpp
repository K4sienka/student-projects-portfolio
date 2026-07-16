#include "DStack.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

StackDItem* createDStack()
{
  return NULL; //0
}

void Dpush( StackDItem** pDStack, double x )                             // wloz na stos
{
  StackDItem* p = ( StackDItem* )malloc( sizeof( StackDItem ) );        //alokacja pamiêci na nowy elemen listy
  if (!p)
  {
    perror( "Dpush: Allocation error\n" );
    return;
  }
  memset ( p, 0, sizeof( StackDItem ) );
  p->key = x;                                     // wstawiæ info do nowego elementu
  p->pNext = *pDStack;                            // dowi¹zaæ do listy(*pNew).pNext;
  *pDStack = p;                                   // przewi¹zaæ wskaŸnik listy na nowy element
}


double Dpop( StackDItem** pDStack )          // zdejmij i zwroc szczytowy eleme stosu
{
  if (!DisEmpty( *pDStack ))                  //musz¹ zgadzac sie typy= gwiazdki
  {
    double x = Dtop( *pDStack );
    Ddel( pDStack );
    return x;
  }
  perror( "Dpop: DStack underflow!!\n" );
  return 0;
}

double Dtop( StackDItem* pDStack )          // zwroc szczytowy elem stosu
{
  if (!DisEmpty( pDStack ))

    return pDStack->key;
  perror( "Dtop: DStack underflow!!\n" );
  return 0;
}

void Ddel( StackDItem** pDStack )         // usun szczytowy (zdejmij)
{
    if (!DisEmpty( *pDStack ))
    {
      StackDItem* p = *pDStack;
      *pDStack = p->pNext;
      free ( p );                       //zwolnienie pamieci
      return;
    }
    perror( "Ddel Stack underflow!\n" );
}
int DisEmpty( StackDItem* pDStack )      // zwraca true jesli stos pusty - else false
{
  return !pDStack;
}
