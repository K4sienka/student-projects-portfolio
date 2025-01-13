#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "ship.h"

#define N         10
#define M         10
#define DEPTH_MIN 5     //glebokosc zanurzenia

typedef enum { UP = 0, RIGHT, DOWN, LEFT } Direction; // kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)

void freeTab( int*** pTab, int nRow, int nCol );
int** CreateTab2D( int nRow, int nCol );
void printTab2D( int** pTab, int nRow, int nCol );

int main( int argc, char* argv[])
{
  if( argc != 2 )
  {
    printf( "Usage: %s <input_file>\n", argv[0] );
    return -1;
  }
  
  int** pTab = CreateTab2D( N, M );       //dynamiczna tablica dwuwymiarowa dla pocz¹tkowej tablicy
  if( !pTab )
  {
    perror( "Error allocation memory (pTab)\n" );
    return -2;
  }

  int** pRoot = CreateTab2D( N, M ); //dyn tab dwuwym dla drogi statku
  if( !pRoot )
  {
    perror( "Error allocation memory (pRoot)\n" );
    return -3;
  }
  
  clearRoot( pRoot, N, M );
  clearRoot( pTab, N, M );       //wyzerowanie obydwu tablic
  if( !setTab( argv[1], pTab, N, M ) )
  {
    printf( "Error open input file %s !!\n", argv[1] );
    return -4;
  }

  printf( "Poziom glebokosci na mapie: \n" );
  printTab2D( pTab, N, M );


  if( !root( pTab, N, M, DEPTH_MIN, 0, 0, pRoot, N - 1, M - 1) )   // Jezeli nie znaleziono drogi od (0,0) do (N,M)
    printf( "Nie ma mozliwosci doplynac do portu!!\n\n" );
  else
  {
    printf( "Trasa statku to: \n" );      //inaczej wypisuje trase
    printTab2D( pRoot, N, M );
  }
       
  
  freeTab( &pTab, N, M );   //zwolnienie pamiêci
  freeTab( &pRoot, N, M );

  return 0;
}


void freeTab( int*** pTab, int nRow, int nCol )
{
  free( **pTab );
  free( *pTab );
  *pTab = NULL;
}

int** CreateTab2D( int nRow, int nCol )     //kreowanie druga metoda
{
  int** pTab = (int**)malloc( sizeof(int*) * nRow );
  if( !pTab ) return NULL;
  memset( pTab, 0, nRow * sizeof( int* ) );

  *pTab = (int*)malloc( nRow * nCol * sizeof( int ) );
  if( !*pTab )
  {
    free( pTab );
    return NULL;
  }
  memset( *pTab, 0, nRow * nCol * sizeof( int ) );

  int** a = pTab + 1;
  int* k = *pTab + nCol;
  for( int i = 1; i < nRow; i++, k += nCol )
    *a++ = k;

  return pTab;
}

void printTab2D( int** pTab, int nRow, int nCol )
{ 
  for( int i = 0; i < nRow; i++ )
  {
    int* ptr = *pTab++;
    for( int j = 0; j < nCol; j++ )
      printf( " %d ", *ptr++ );
    printf( "\n\n" );
  }
}


