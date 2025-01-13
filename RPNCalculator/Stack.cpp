#include "Stack.h" 
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

StackItem* createStack()
{
  return NULL; //0
}


void push( StackItem** pStack, char x )                               // wloz na stos
{
  StackItem* p = ( StackItem* )malloc( sizeof( StackItem ) );         //alokacja pami�ci na nowy elemen listy
  if (!p)
  {
    perror( "Push: Allocation error\n" );
    return;
  }
  memset ( p, 0, sizeof( StackItem ) );
  p->key = x;                                                         // wstawi� info do nowego elementu
  p->pNext = *pStack;                                                // dowi�za� do listy(*pNew).pNext;
  *pStack = p;                                                       // przewi�za� wska�nik listy na nowy element
}

char pop( StackItem** pStack )            // zdejmij i zwroc szczytowy eleme stosu
{
  if( !isEmpty( *pStack ) )               //musz� zgadzac sie typy= gwiazdki
  {
     char x = top( *pStack );
     del( pStack );
     return x;
  }
  perror( "Pop Stack underflow!!\n");
  return 0;
}

char top( StackItem* pStack )          // zwroc szczytowy elem stosu
{
  if (!isEmpty( pStack ))
    return pStack->key;                 //( *pStack ).key/\
  //err
  return 0;
}
void del( StackItem** pStack )         // usun szczytowy (zdejmij)
{
  if( !isEmpty( *pStack ) )
  {  
    StackItem* p = *pStack;
    *pStack = p->pNext;
    free ( p );                          //zwolnienie pamieci
     return;
  }
  perror( "Del Stack underflow!\n" );
}
int isEmpty( StackItem* pStack )      // zwraca true jesli stos pusty - else false
{
  return !pStack;
}
