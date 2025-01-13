#include <stdio.h>
#include <memory.h>
#include "ship.h"


#define N         10
#define M         10
#define DEPTH_MIN 5     //glebokosc zanurzenia

typedef enum { UP = 0, RIGHT, DOWN, LEFT } Direction; // kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)


void clearRoot( int** pRoot, int nRow, int nCol ) //zeruje
{
  memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
  FILE* fin = NULL;               //wczytuje dane z pliku
  if((fin = fopen( sFile, "rt" )) == NULL ) //jesli chce ¿eby z folderu "wy¿ej" wczytal to "\\nazwa_folderu\\Plik.txt"
  {
    //perror( "Error open input file\n" );
    return 0;
  }

  for( int i = 0; i < nRow; i++ )
  {
    int* t = *pTab++;                           //pTab to tablica glebokosci
    for( int j = 0; j < nCol; j++ )       //nRow i nCol wymiary tablicy
      fscanf( fin, "%d", t++ );
  }
  fclose( fin );
  return 1;
}


int move( int** pTab, int nRow, int nCol, int nDepth, int moving, int x, int y, int* px, int* py, int** pRoot )
{
  switch( moving )                               // x,y to wsp skad robimy nowy ruch, obliczamy nowe wsp px/py
  {
  case UP:    *px = x - 1; *py = y;     break;
  case DOWN:  *px = x + 1; *py = y;     break;
  case RIGHT: *px = x;     *py = y + 1; break;
  case LEFT:  *px = x;     *py = y - 1; break;
  default: perror( "Wrong direction" ); break;
  }

  if( *px >= 0 && *py >= 0 && *px < nRow && *py < nCol ) // czy nowe px/py s¹ w zakresie tablicy
    if( pTab[*px][*py] > nDepth && !pRoot[*px][*py] )   //spr czy moze przeplynac && czy statek juz nie byl w tej lokalizacji
      return 1;
  return 0;
}



int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{
  static int moveNo = 1;    //sledzenie liczby ruchow
  pRoot[x][y] = moveNo++;     //zapamietywanie drogi, kolejny ruch

  if( x == x_dest && y == y_dest )  //dotarlo do portu
  {
    printf( "\n" );
    return 1;
  }
    int px = 0;
    int py = 0; //nowe wsp jesli nie dotarl

    for( int nr = UP; nr <= LEFT; nr++ ) //sprawdzanie mozliwosci ruchu statku
    {
      if( move( pTab, nRow, nCol, nDepth, nr, x, y, &px, &py, pRoot ) )  //move jesli ruch mozliwy
      {
        if( root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) )            //jesli sie powiodlo root
          return 1;
      }
    }
    pRoot[x][y] = 0;            //ruch zly, wiec ustawiamy na 0,0
    moveNo--;

  return 0;
}


