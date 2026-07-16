#ifndef _UTIL_
#define _UTIL_

#include <stdio.h>

char    getOper();
int     isOper( char c );                                   //czy jest operator
double  getNum();                                           //branie liczby
double  Eval( double arg1,  char oper, double arg2 );       //liczy
int     prior( char oper );                                 //priorytet

#endif
