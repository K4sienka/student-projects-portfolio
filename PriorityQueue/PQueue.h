#pragma once
#include "global.h"

#define PRIOR_ERROR   INT_MIN      //jako minimalna wartosc calkowita
#define POS_ERROR     -1   //jako wartosc ujemna np -1 (indeks tablicy jakiego nie ma!)


typedef struct   // zachowac oryginalne nazwy!!!!!!  
{
  PQINFO* pInfo;       // Ptr to user info  
  int nPrior;      // prior value (int) for the user info  
} PQItem;         // type of the queue item


typedef struct   // zachowac oryginalne nazwy!!!!!!
{
  PQItem* pPQueue;     // kolejka realizowana w postaci stogu  (dynamiczna tablica)
  int nPQSize;      // rozmiar calkowity kolejki priorytetowej
  int nPQCurrSize;  // ilosc elementow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 

} PQueue;


PQueue* PQCreate( int nSize );

int PQisEmpty( PQueue* pQueue );

int PQSize( PQueue* pQueue );

int PQMaxPrior( PQueue* pQueue );

int PQEnqueue( PQueue* pQueue, PQINFO* pInfo, int nPrior );

PQINFO* PQDequeue( PQueue* pQueue );

void PQClear( PQueue* pQueue, void( __cdecl* freemem )(const void*) );

void PQRelease( PQueue** pQueue, void( __cdecl* freemem )(const void*) );

void PQPrint( PQueue* pQueue, int i, void( __cdecl* y )(const void*) );

int PQSetPrior( PQueue* pQueue, PQINFO* pInfo, int nPrior, int( __cdecl* compare )(const void*, const void*) );

int PQsetPrior( PQueue* pQueue, int a, int b );

int PQGetPrior( PQueue* pQueue, PQINFO* pInfo, int( __cdecl* compare )(const void*, const void*) );

int PQgetPrior( PQueue* pQueue, int i );

int PQFind( PQueue* pQueue, PQINFO* pInfo, int( __cdecl* c )(const void*, const void*) );


