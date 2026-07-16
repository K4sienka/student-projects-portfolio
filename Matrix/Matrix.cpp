#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "Matrix.h"


void Complement( double** pTab0, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix( double** pTabD, double** pTab, int nDim );

#define ZERO 1e-30

int     CreateMatrix( double*** pTab, int nDim )   //tworzy macierz do ktorej wczytywane sa dane z pliku
{
  *pTab = (double**)malloc( nDim * sizeof( double* ) ); //wystarczy nDim, bo macierz kwadratowa
  if( !*pTab ) return 0;
  memset( *pTab, 0, nDim * sizeof( double* ) );

  double** p = *pTab;
  for (int i = 0; i < nDim; i++, p++)
  {
    *p = (double*)malloc( nDim * sizeof( double ) );
    if( !*p ) return 0;
    memset( *p, 0, nDim * sizeof( double ) );
  }
  return 1;
}

void    DeleteMatrix( double*** pTab, int nDim )  // zwolnienie pamiêci
{
  double** v = *pTab;
  for( int i = 0; i < nDim; i++ )
    free( *v++ );

  free( *pTab );
  *pTab = NULL;
}

void    PrintMatrix( double** pTab, int nDim ) // drukuje macierz 
{
  for( int i = 0; i < nDim; i++ )
  {
    double* p = *pTab++;
    for( int j = 0; j < nDim; j++ )
    printf( " %.3f ", *p++ );

    printf( "\n\n" );
  }
}

void    TransMatrix( double** pTab, int nDim ) // transponowanie macierzy (bez pomocniczej, raz wolno indeksowac)
{ 
  double** v = pTab;                    //wskaŸnik do tablicy wejœciowej
  for( int i = 0; i < nDim; i++ )        // po wierszach
  {
    double* p = *v++ + 1 + i;           // wskaznik na nastepny elem w wierszu
    for( int j = i + 1; j < nDim; j++, p++ ) // iteracja po pozosta³ych kolumnach     /r += nDim w for
    {
      double temp = *p;                 // zamiana kolumn z wierszami
      *p = pTab[j][i];                   //*p=*r
      pTab[j][i] = temp;                //*r=temp
    }
  }
}

void    InverseMatrix( double** pInv, double** pTab, int nDim, double det ) // macierz odwrotna, na we obliczony wczesniej w main() det  (det!=0)
{ 
  ComplMatrix( pInv, pTab, nDim ); //macierz dopelnien
  TransMatrix(pInv, nDim);        //transponowac

    for( int i = 0; i < nDim; i++ )
    {
      double* t = *pInv++;
      for( int j = 0; j < nDim; j++ )
        *t++ /= det;                  //liczenie elementu tablic odwroconej
    }
}

double  Det( double** pTab, int nDim ) // wyznacznik rekurencyjnie, rozwiniecie wzgl 0-go wiersza, (dla 2x2 uzyc znanego wzoru - mozna zaindeksowac)
{
    if( nDim == 1 ) return **pTab;
    if( nDim == 2 ) return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];
    
    double** detTab = NULL;
    if( !CreateMatrix( &detTab, nDim - 1 ) )
    {
      perror( "Error create in Det!\n" );
      return 0;
    }

    double det = 0;
    int symbol = 1;     // znak wyznacznika, na koncu zmieniana na przeciwn¹, zeby dodawaæ i odejmowaæ kolejne elem z det

    double* x = *pTab;

    for( int j = 0; j < nDim; j++ ) 
    {
      Complement( detTab, pTab , 0, j, nDim );         
      det += *x++ * symbol* Det( detTab, nDim - 1 ) ;      //wczesniej pTab[0][j]
      symbol = -symbol;

    }
    DeleteMatrix( &detTab, nDim-1 );
  return det;
}

void LayoutEqu( double** pInv, double* pB, double* pRes, int nDim )  // rozwiazuje ukl rownan
{
    for( int i = 0; i < nDim; i++, pRes++ ) // Tworzenie wektora wynikowego
    {
      double* x = *pInv++;      //x to pocz¹tek kolejnego wiersza macierzy odwrotnej pInv
      double* y = pB;           // y to kolejny element wektora wyrazów wolnych pB
      for( int j = 0; j < nDim; j++ ) 
      {
     *pRes += *x++ * *y++;    // mno¿enie wartoœci macierzy odwrotnej i wektora kolumny z wynikami
      }
    }
}

void Complement(double** pTab0, double** pTabI, int nRow, int nCol, int nDim)
{
    for( int i = 0; i < nDim; i++, pTabI++ ) 
    {
      if( i == nRow ) continue;        //pomijanie wierszy, dla ktorej tworzymy dopelnienie
      double* wy = *pTab0++;         //wskaznik na aktualny elem macierzy wy
      double* we = *pTabI;           //wskaznik na aktualny elem macierzy we
      for( int j = 0; j < nDim; j++, we++ ) 
      {
        if( j == nCol ) continue;        //pomijanie kolumny
        *wy++ = *we;                       //przypisywanie elem wyj i we
      }
    }
}

void ComplMatrix( double** pTabD, double** pTab, int nDim ) // oblicza macierz dopelnien pTabD na podstawie tablic wejsc pTab
{
  double** cMatrixTab = NULL;

  if( !CreateMatrix( &cMatrixTab, nDim - 1 ) )
  {
    perror( "Error create matrix in ComplMatrix!!\n" );
    //return -1;
  }
  int x = 1;

  for (int i = 0; i < nDim; i++)
  {
    double* c = *pTabD++;
    int znak = ((i % 2) ? (-1) : (1));
    for (int j = 0; j < nDim; j++)
    {
      Complement( cMatrixTab, pTab, i, j, nDim );  // macierz wyznacznikow   
      double potega = znak * Det ( cMatrixTab, nDim - 1 );   //zmiana znakow
      *c++ = potega;          // przypisywanie do elem macierzy
      znak = -znak;
    }
  }
  DeleteMatrix( &cMatrixTab, nDim - 1 );
}
