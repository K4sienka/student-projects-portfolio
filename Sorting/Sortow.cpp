#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "Sort.h"

  // INSTRUKCJE DLA PORÓWNYWANIA CZASÓW SORTOWAÑ
  //zdefiniowac tablice wzorcem pattern
  //zainicjowaæ losowo pattern
  //zdefiniowaæ tablice do sortowania tab
  //wpisac nazwe sortowania
  //wkopiowaæ pattern do tab
  //odczytac czas
  //posortowaæ i wyliczyæ czas w milisekundach
  //wypisaæ czas
  //wypisac tablice lub jej fragment

#define MAXTAB 50
#define MAXLINE 10
//#define _PRINT_TAB


int createTab( int** pTab, int nSize ); //parametry wyjsciowe
void printTab( int* pTab, int nSize );
void freeTab( int** pTab);
void initTab( int* pTab, int nSize );
void copyTab( int* pDest, int* pSource, int nSize );


/*double count(int* tab, int size);
void copyTab( int* pDest, int* pSource, int nSize );

void BubblesSort( int* pTab, int nSize) ;
void SimpleSort( int* pTab, int nSize );
void SimpleSelectionSort( int* pTab, int nSize );
void MixedSort( int* pTab, int nSize );
void HalfInsertionSort( int* pTab, int nSize );*/


typedef void (*pFun)(int*, int);      //typ wskaznikowy na funkcje void z parametrami int*, int (pFun)


int main( int argc, char* argv[] )
{
  if ( argc != 2 )
  {
    printf( " Usage: %s <tab_size> \n ", argv[0] ); //uzycie
    return 1;
  }
  int nSize = atoi( argv[1] );      //odczytanie rozmiaru

  int* pPattern = NULL;
  if (!createTab( &pPattern, nSize ))
  {
    perror( "Allocation ERROR - pPattern!\n" );
    return 2;
  }

  //int pattern[MAXTAB] = {0};
  initTab( pPattern, nSize );
  //int tab[MAXTAB] = { 0 };
  int* pTab = NULL;
  if (!createTab( &pTab, nSize ))
  {
    perror( "Allocation ERROR - pTab!\n" );
    return 3;
  }

  initTab( pTab, nSize );

#ifdef _PRINT_TAB
   printf( " The table to sort is: \n\n " );    //++NA WARUNKOWEJ KOMPILACJI: _PRINT_TAB
   printTab( pTab, (nSize < MAXTAB) ? nSize : MAXTAB ); // Wydrukuj losow¹ tablice
  printf( " \n\n " );
#endif

  //zdefiniowac tablice (SortFun) adresow funkcji sortujacych bezrozmiarowo zainicjowana 
  //nazwami funkcji sortujacych
//zdefiniowac tablice (SortNames) bezrozmiarowo zainicjowana stringami - nazwami sortowan 
  // SortNames[i] odpowiada SortFun[i]

  pFun pSort[] = { BubblesSort, SimpleSort, SimpleSelectionSort, MixedSort, HalfInsertionSort, HeapSort, QuickSort };
  const char* pList[] = {"BubblesSort", "SimpleSort", "SimpleSelectionSort", "MixedSort", "HalfInsertionSort", "HeapSort", "QuickSort"};

  //zrobic petle for wczesniej obliczyc ilosc iteracji 
  //(rozmiar tablic, sizeof sortowania/sizeof typ elementu tablicy)
  int no = sizeof( pSort ) / sizeof( pFun );
  for (int i = 0; i < no ; i++) //wyœwietlanie sortowania i czasu
  {
    printf( "%s\n\n", pList[i] );
    copyTab( pTab, pPattern, nSize );
    //double past = 0;
    double begin = clock();
    pSort[i]( pTab, nSize );
    double past = (double)(clock() - begin) / CLOCKS_PER_SEC;   //licz czas sortowania

    
    printf( "Sorting took: %f [s]\n", past );
  
    #ifdef _PRINT_TAB
    printf( " Sorted table: " );
    printTab( pTab, (nSize < MAXTAB) ? nSize : MAXTAB ); //Drukuj posortowan¹ tablice
    printf( " \n\n " );
    #endif
  }


  /*clock_t begin1;
  clock_t end1;
  double past1 = 0;
  begin1 = clock();
  NAZWA SORTOWANIA( pTab, nSize );
  end1 = clock();
  past1 = ( double)(end1 - begin1 ) / CLOCKS_PER_SEC;   //licz czas sortowania

  printTab( pTab, (nSize < MAXTAB) ? nSize : MAXTAB ); //Drukuj posortowan¹ tablice
  printf( " Sorting algorithms' times comparison: " );
  printf( " \n\n " );
  printf( " HEAP sorting took %lf [s] ", past1 );
  printf( " \n\n " );*/



  freeTab( &pTab );
  freeTab( &pPattern );

  return 0;
}

int createTab( int** pTab, int nSize ) //funckja odpowiedzialna za alokowanie pamiêci
{
  *pTab = (int*)malloc( nSize * sizeof( int ) );
  if (!*pTab) //==NULL
    return 0;
  memset( *pTab, 0 , nSize * sizeof( int ) );
  return 1;
}

void initTab( int* pTab, int nSize )
{
  srand( ( unsigned int )time(NULL) );  //losowanie elementów tablicy
  for ( int i = 0; i < nSize; i++ )
    *pTab++ = rand() % nSize;
}

void printTab( int* pTab, int nSize )
{
  for ( int i = 0; i < nSize; i++ )
  {
    printf( " %d", *pTab++ );   //drukowanie elementów nowej tablicy
    if ( (i + 1) % MAXLINE == 0 )
      printf( " \n " );
  }
  printf( " \n " );

}
void freeTab( int** pTab ) //zwalnianie pamiêci
{
  free( *pTab );
  *pTab = NULL;
}

void copyTab( int* pDest, int* pSource, int nSize )
{
  memcpy( pDest, pSource, nSize * sizeof(int) );            //kopiuje pamiec pod adres pDest
}