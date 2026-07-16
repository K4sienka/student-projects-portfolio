
#ifndef _STACK_H
#define _STACK_H

// naglowki funkcji publicznych modulu
//zdefiniowac typ elementu listy prostej StackItem z polami struktury: key i pNext

typedef struct tagStackItem
{
  char          key;
  tagStackItem* pNext;

}StackItem;

StackItem* createStack();


//jesli funkcja modyfikuje stos to **, jeœli nie * (parametry wejsciowe i wyjsciowe czy ulegaj¹ zmianie w funkcji)


void push( StackItem** pStack, char x );          // wloz na stos
char pop( StackItem** pStack );                   // zdejmij i zwroc szczytowy eleme stosu
char top( StackItem* pStack );                    // zwroc szczytowy elem stosu
void del( StackItem** pStack );                   // usun szczytowy (zdejmij)
int isEmpty( StackItem* pStack );                 // zwraca true jesli stos pusty - else false

#endif
