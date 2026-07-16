#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "Matrix.h"

#define _DEBUG_

#define MIN 1e-30

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );
int CreateVectors( double** pTab, int nSize );
void Vectors( double* v, int nSize);


int main( int argc, char** argv )
{

  if( argc != 2 )                 // sprwdzic argumenty main
  {
    printf( "Usage: %s <input_file>\n", argv[0] );
    return 1;
  }

  FILE* fin = NULL;                                // odtworzyc plik do odczytu (tekstowy)

  if( (fin = fopen( argv[1], "rt" )) == NULL ) 
  {
    printf( "Error open %s input file\n", argv[1] );
    return -1;
  }
  
  double** pMatrix = NULL;
  int nDim = 0;
  
#ifdef _DEBUG_      
  fscanf( fin, "%d", &nDim );       // odczytac rozmiar nDim   fscanf( fin, "%d\n", &nDim ); (nDim parametr WY, fin plik po otwarciu do odczytu)
  printf( "Wymiar macierzy: %d\n\n" , nDim );
#endif

  
  if (!CreateMatrix( &pMatrix, nDim ))      // wykreowac macierz pMatrix ukladu nDim x nDim
  {
    printf( "Error in creating matrix!\n" );
    return -2;
  }

  double* x = NULL;         // wykreowac wektor wyrazow wolnych
  if( !CreateVectors( &x, nDim ) ) 
  {
    printf( "Error in creating vector!\n" );
    return -3;
  }
 
   ReadData( fin, pMatrix, x, nDim );        // wczytac dane ( ReadData() )


#ifdef _DEBUG_                                 //wydruk kontrolny (warunkowa kompilacja)
    printf( "Wczytana macierz: \n" );
    PrintMatrix( pMatrix, nDim );
    printf( " Wektory wyrazow wolnych: \n" );
    Vectors( x, nDim );
#endif

    double det = Det( pMatrix, nDim );      // obl wyznacznik

#ifdef _DEBUG_                          //wydruk kontrolny (warunkowa kompilacja)
    printf( "\nWyznacznik macierzy: %.1f\n", det );
#endif 

    if( fabs( det ) < MIN )       //fabs to funckja która oblicza wart bezwzglêdn¹
    {
      printf( "Wyznacznik równy 0!\n" );
      return -4;
    }


    double** Inverted = NULL;
    if( !CreateMatrix( &Inverted, nDim ) ) 
    {
      printf( "Error in creating Invered Matrix!\n" );
      return -5;
    }

    InverseMatrix( Inverted, pMatrix, nDim, det );  // obrocic macierz
  
#ifdef _DEBUG_                               //wydruk kontrolny  (warunkowa kompilacja)
    printf( "Macierz odwrotna: \n" );
    PrintMatrix( Inverted, nDim );
#endif

    double* VRes = NULL;
  if( !CreateVectors( &VRes, nDim ) ) // wykreowac wektor wynikowy
  {
    printf( "Error in creating vectors!\n" );
    return -6;
  }
  LayoutEqu( Inverted, x, VRes, nDim ); // rozwiazac ukl
  printf( "Wektory wynikow: \n" ); // wyniki
  Vectors( VRes, nDim );
  DeleteMatrix( &pMatrix, nDim );
  DeleteMatrix( &Inverted, nDim );

  free( VRes );              // zwolnic pamiec
  free( x );

  return 0;
}


void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{
  for( int i = 0; i < nDim; i++, pMatrix++ )
  {
    double* t = *pMatrix;
    for( int j = 0; j < nDim; j++, t++ )
    {
      fscanf( fin, "%lf", t );
    }
    fscanf( fin, "%lf", b++ );
  }
  fclose( fin );
}

int CreateVectors( double** cv, int nSize )   //tworzy wektory wyrazow wolnych
{
    *cv = (double*)malloc( nSize * sizeof( double ) );
    if( !*(cv) ) return 0;
    memset( *cv, 0, nSize * sizeof( double ) );

    return 1;
}

void Vectors( double* v, int nSize ) //drukuje wektory wyrazow wolnych
{
    for( int i = 0; i < nSize; i++, v++ )
        printf( "x%d = %0.1lf\n", i + 1, *v );
}