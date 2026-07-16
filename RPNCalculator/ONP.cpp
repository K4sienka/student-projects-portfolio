#include <iostream>
#include <stdio.h>
#include "DStack.h"
#include "Stack.h" 
#include "Util.h"

double ONP();


int main()
{

  printf( "Podaj wyrazenie:" );
  printf( "Wartosc wyrazenia = %lf\n", ONP() );  
  
  return 0;
}

 double ONP() 
{
  StackItem* pStack = createStack();                            //wykreowac stos operatora
  StackDItem* pDStack = createDStack();                         //wykreowac stos operanda

  char elem;
  Dpush( &pDStack, getNum() );                                 //wstaw na stos operanda
  
  while( isOper ( elem = getOper() ) )                         //wczytanie potencjalnego operatora i spr czy operator
  {
     while( prior ( elem ) <= prior ( top( pStack ) ) )         //prior operatora<=prior szczytu stosu operatora
     {
       double dzialanie = Dpop( &pDStack );                    // liczymy: sciagnac drugi, potem pierwszy argument operatora
       Dpush( &pDStack, Eval( Dpop( &pDStack ), pop( &pStack ), dzialanie ) );       //obliczyc i wynik wstawic na stos liczbowy
     }
     push( &pStack, elem );                                                           //wczytac liczbe (operand)
      Dpush( &pDStack, getNum() );                                                      //wstawic na stos liczbowy
  }
  while( !isEmpty( pStack ) )
  {
    double dzialanie = Dpop( &pDStack );                                               //liczymy: sciagnac drugi argument operand
    Dpush( &pDStack, Eval( Dpop( &pDStack ), pop( &pStack ), dzialanie ) );            //sciagnac pierwszy argument, operator, obliczyc i wynik wstawic na stos liczbowy
  }

  return Dpop( &pDStack );
}



 /*double ONP() // 1+2*3/1+2
 {
     createStack();    //wykreowac stos operatora
     createDStack();   //wykreowac stos operanda
     double elem = getNum();   //wczytaj operand
     Dpush ( elem ); //wstaw na stos operanda
   while ( isOper ( elem = getOper() ) )   //wczytanie potencjalnego operatora i spr czy operator
   {
      while (prior ( elem ) <= prior ( top() ) ) //prior operatora<=prior szczytu stosu operatora
      {
        double dzialanie = Dpop();     // liczymy: sciagnac drugi, potem pierwszy argument operatora
        Dpush ( Eval( Dpop(), pop(), dzialanie ) );       //obliczyc i wynik wstawic na stos liczbowy
      }
      push ( elem );//wczytac liczbe (operand)
       Dpush( getNum() ); //wstawic na stos liczbowy
   }
   while ( !isEmpty() )
   {
     double dzialanie = Dpop();      //liczymy: sciagnac drugi argument operand
     Dpush ( Eval( Dpop(), pop(), dzialanie ) );//sciagnac pierwszy argument, operator, obliczyc i wynik wstawic na stos liczbowy
   }

   return Dpop();
 }*/