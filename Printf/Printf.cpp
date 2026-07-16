#include <stdio.h>
#include <stdarg.h>                 // potrzebne dla funkcji wielu zmiennych
#include <iostream>

int Printf( const char* sFormat, ... );                 //zadeklarowac parametry
int PrintfV( const char* sFormat, va_list args );

void outDec( int );         // znakowo wypisuje liczbe calk ujemne
void outChar( char );       // wypisuje znak  // putchar()
void outStr( char* );       // wypisuje znakowo string
void outDouble( double );   // wypisuje znakowow liczbe double    0.
void outNum( int x );       // wypisuje znakowo liczbe int >0     rekurencyjnie


int main( int argc, char* argv[] )
{
  int n = -0;
  char c = '#';
  double x = 12000000.34060700012984009;     // .0000012 <=1e-5
  double y = -.12;
  double z = -0.5;
  char* str = (char*)"To jest string";

  Printf( "%s\n%f %c  n=%d \ny=%f ````` z=%f\n  ~~'@% ", str, x, c, n, y, z );
  return 0;
}

// implementacja uproszczonej funkcji "Printf": %c %d %f %s oraz 
// zamienia `(klawisz ~) na '( klawisz ")
// do wypisywania mozna uzyc JEDYNIE outChar() -


int Printf( const char* sFormat, ... ) // ... odpowiada za nieokreslona ilosc parametrow
{
  va_list args;                            //liczy liczbe argumentow
  va_start ( args, sFormat );              //tworzy liste arg
  int ret_val = PrintfV( sFormat, args );
  va_end( args );
  //ret_val;
  //int res=
  //return res;
  return ret_val;
}


int PrintfV( const char* sFormat, va_list args )
{
  char c;
  while (c = *sFormat++)  // *sFormat= znak z wejscia stringu
  {
    switch (c)
    {
    case '%':
      switch (c = *sFormat++)
      {
      case 'd': outDec( va_arg( args, int ) ); break;
      case 'f': outDouble( va_arg( args, double ) ); break;
      case 's': outStr( va_arg( args, char* ) ); break;
      case 'c': outChar( va_arg( args, char ) ); break;
      default: outChar ( '%' );      //jezeli jest cos innego, to wypisuje to co bylo wpisane za %
        if ( c && c != '%' ) outChar( c ); else *sFormat--; break; //musi byc warunek na sytuacje %%%(...)
      }
      break;
    case '`':  c = '\'';  //podstawia normalny apostrof, \ usuwa znaczenie znaku specjalnego 
    default: outChar( c ); break;
    }
  }
  return 1;

}

void outChar( char c ) //znak
{
  putchar( c );
}

void outStr( char* pStr ) //string
{
  while (*pStr)
    outChar( *pStr++ );
}

void outDouble( double x ) //przecinkowe
{
  if (x < 0)  // czy ujemna
  {
    outChar( '-' );
    x = -x;
  }
  outNum ( (int)x ); //czesc calkowita liczby
  outChar( '.' );
  x = x - (int)x;
  for (int i = 0; i < 9; i++)         //i to ilosc liczb po przecinku
  {
    outChar( int( x *= 10 ) % 10 + '0' ); //wypisanie liczby Hornerem
  }
}

void outDec( int x ) //calkowite ujemne
{
  if (x < 0)  // czy ujemna
  {
    outChar( '-' );  // jak tak to wypisz -
    x = -x;
  }
  outNum ( x );
}

void outNum( int x ) //rekurencyjnie dla calkowitych wielocyfrowych
{
  if (x > 9)  // czy wielocyfrowa
    outNum( x / 10 );   // rekurencja dla dziesi¹tek

  outChar( x % 10 + '0' );  // Horner
}

