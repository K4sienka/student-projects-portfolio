#include "Util.h"
#include <math.h>

#define MIN 1e-7284

void skipSpaces();
int isDigit( char c );

char    getOper()
{
  skipSpaces();
  return getchar();
}
int  isOper( char c )
{
  switch (c)
  {
   case '+': 
   case '-': 
   case '*': 
   case '/': 
   case '^': return 1;
  }
  return 0;
}
double getNum()
{
  double res = 0;
  char c;
  skipSpaces();
  while (isDigit( c = getchar() ))
    res = res * 10 + (c - '0');
  
  if (c == '.')
  {
    double coef = 0.1;
    while (isDigit( c = getchar() ))
    {
      res += coef * (c - '0');
      coef *= 0.1;
    }
  }
  ungetc ( c, stdin );
  return res;
}

double  Eval( double arg1, char oper, double arg2 ) 
{
  switch (oper)
  {
    case '+': return arg1 + arg2;
    case '-': return arg1 - arg2;
    case '*': return arg1 * arg2;
    case '/': if (arg2 > MIN )  return arg1 / arg2; perror( "Division by ZERO!\n" ); break;
    case '^': return pow( arg1, arg2 );
  }
  return 0;

}
int     prior( char oper )
{
    switch ( oper )
    {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    }
    return 0;
}

void skipSpaces()
{
  char c;
  while ( (c = getchar()) == ' ' || c== '\t' );           //zwraca wartoœæ warunku
  ungetc( c, stdin );                                     //oddaje znak do bufora klawiatury, cofa znak i go zapamiêtuje
}
int isDigit( char c )
{
  return ( c >= '0') && (c <= '9' );
}