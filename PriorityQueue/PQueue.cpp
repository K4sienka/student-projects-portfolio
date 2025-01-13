#include "PQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

void UpdateDown( PQItem* stog, int l, int p );
void UpdateUp( PQItem* stog, int l, int p );

PQueue* PQCreate( int nSize ) // kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad
{
  if( nSize <= 0 )   return NULL;
  PQueue* pq = ( PQueue* )calloc( 1, sizeof( PQueue ) ); //alokacja pamieci
  if( !pq )   return NULL;

  pq->pPQueue = ( PQItem* )calloc( nSize, sizeof( PQItem ) ); //do przechowywania elementow kolejki 
  if( pq->pPQueue == NULL )    return NULL;
  pq->nPQSize = nSize; //wskazanie na caly rozmiar kolejki
  //pq->nPQCurrSize = 0; // na pocz¹tku kolejka jest pusta
  return pq;
}

int PQisEmpty( PQueue* pq )  // zwraca 0 -nie pusta lub 1 - kolejka pusta
{
  return !pq && !( pq->nPQCurrSize );
}

int PQSize( PQueue* pq )     // zwraca ilosc elementow w kolejce
{
  return ( pq ) ? pq->nPQCurrSize : PRIOR_ERROR; // pq->nPCRussSize to wsk na aktualn¹ liczbe elementow kolejki
}

int PQMaxPrior( PQueue* pq ) // zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR
{
  return (!PQisEmpty( pq )) ? PQgetPrior( pq, 0 ) : PRIOR_ERROR;
}

int PQEnqueue( PQueue* pq, PQINFO* pInfo, int nPrior )  //wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)
{             //ANALOGIA DO LISTY I PREZENTACJI
  if( PQisEmpty( pq ) ) return 0;
 int x = PQSize( pq );
 if( x >= pq->nPQSize ) return 0; //jesli kolejka jest juz pelna

  pq->pPQueue[x].nPrior = nPrior; //przypisanie zadany priorytet do elem kolejki o indeksie x
  pq->pPQueue[x].pInfo = pInfo; //przypisanie wskaznika pInfo do elem kolejki o indeksie x
  if ( x > 0 ) UpdateUp( pq->pPQueue, 0, x );// uaktualnic w gore  
  ++( pq->nPQCurrSize ); //zwiekszenie rozmiaru kolejki
   return 1;
}

PQINFO* PQDequeue( PQueue* pq )  // zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie
{                       //ANALOGIA DO LISTY I PREZENTACJI
  //if(!PQSize( pq )) return 0;//kolejka jest pusta
  if( PQisEmpty( pq ) ) return NULL; //jesli puste to nie ma co usuwac
  int x =--pq->nPQCurrSize; 
  PQINFO* y = pq->pPQueue[0].pInfo; //przypisanie wskaŸnika do pInfo pierwszego elementu do y
  if( x > 0 ) pq->pPQueue[0] = pq->pPQueue[x]; //wartosc ostatniego elem kolejki przypisany do pierwszego
  memset( pq->pPQueue + x, 0, sizeof( PQItem ) ); //wyzerowanie pamieci dla usunietego elementu
  if( PQSize( pq ) > 1 ) UpdateDown( pq->pPQueue, 0, x - 1 ); // uaktualnic w dol
  return y;
}

void PQClear( PQueue* pq, void( __cdecl* freemem )(const void*) )    // czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura 
// do zwolnienia dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 
{                           //ANALOGIA DO LISTY
    
  if( !freemem )//sprawdzenie funkcji
  {
    perror( "ERROR IN PQClear!(freemem)\n" );
    return;
  }
  
  if( !pq )//sprawdzenie kolejki
  {
    perror( "ERROR IN PQClear!(pq)\n" );
    return;
  }
  while( PQisEmpty( pq ) ) //dopoki lista nie jest pusta
    freemem( PQDequeue( pq ) ); //zwolnienie
}

void PQRelease( PQueue** pq, void( __cdecl* freemem )(const void*) )  // usuwa cala kolejke, zwraca w parametrze we-wy NULL (kolejka) usuwaj¹c wszyskto 
// wczesniej (czyszczenie kolejki)
{                     //JAK W LISCIE
  if( !pq || !*pq )
  {
    perror( "ERROR IN PQRelease!(pq)\n" );
    return;
  }
  PQClear( *pq, freemem ); //usuniecie i zwolnienie wszystkich elem
  free( (*pq)->pPQueue );
  free( *pq );   //zwolnienie pamieci glowy
  *pq = NULL;    //lista to NULL
}

void PQPrint( PQueue* pq, int i, void( __cdecl* printitem )(const void*))  // drukuje preorder od zadanej pozycji, aby wydrukowaæ info uzytkownika 
// przekazac trzeba funkcje drukujaca ta informacje, drukuje priorytet w okraglych nawiasach oraz pozycje w  kolejce w kwadratowych nawiasach
{
  //pq to wskaznik na strukture kolejki, y to wskaznik na funkcje drukuj¹c¹ elem, i to pozycja w kolejce
  if( !pq || !printitem || i < 0)      //koniec jak skonczy sie lista 
  {
    perror( "Brak kolejki, bledny adres funckji, i<0!\n" );
      return;
  }
  //if( !printitem ) return; 
  if( i < PQSize(pq) )
  {
      printitem( pq->pPQueue[i].pInfo ); //Jeœli y nie 0 to wywo³aæ i przekazaæ jako argument wsk na pInfo z pozycji i
    printf( " Priorytet: (%d); Indeks: [%d] \n", pq->pPQueue[i].nPrior, i );
    PQPrint( pq, 2 * i + 1, printitem );    //rekurencja  dla lewego dziecka na pozycji i
    PQPrint( pq, 2 * i + 2, printitem );    //dla prawego
  }
}

int PQSetPrior( PQueue* pq, PQINFO* pInfo, int nPrior, int( __cdecl* compare )(const void*, const void*) ) // ustawia nowy priorytet dla zadanej informacji uzytkownika, 
//nie znana struktura informacji, która trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika. 
// Funkcja zwraca poprzedni priorytet lub PRIOR_ERROR 
{
  return PQsetPrior( pq, PQFind( pq, pInfo, compare ), nPrior ); //przez PQFind szuka elem ktoremu trzeba nadaæ priorytet przez setPrior
}

int PQsetPrior( PQueue* pq, int a, int b ) // ustawia nowy priorytet dla informacji uzytkownika bedacej na zadanej pozycji w kolejce 
// (indeks w stoglicy). Funkcja zwraca poprzedni priorytet. W przypadku bledu zwraca PRIOR_ERROR 
{     //w to stary priorytet, b to nowy
  if( PQisEmpty(pq) ) return PRIOR_ERROR;

  int w = PQgetPrior(pq, a); //wywoluje poprzedni priorytet informacji 
  if( w == POS_ERROR ) return PRIOR_ERROR;
  pq->pPQueue[a].nPrior = b; //nowy priorytet b dla nowego elementu a
  if( b > w ) UpdateUp( pq->pPQueue, 0, a  ); //jesli wiekszy to trzeba posortowac w gore
  else if( b < w ) UpdateDown( pq->pPQueue, a, PQSize( pq ) - 1 ); //inaczej w dol
  return w; //jak rowne to po prostu zwrocic
}

int PQGetPrior( PQueue* pq, PQINFO* pInfo, int( __cdecl* compare )(const void*, const void*) ) // zwraca priorytet informacji uzytkownika w kolejce lub PRIOR_ERROR, nie znana struktura informacji, która 
// trzeba wyszukac dlatego nalezy przekazac funkcje porownujaca informacje uzytkownika  
{
  return PQgetPrior( pq, PQFind(pq, pInfo, compare) );//indeks wyszukiwanej informacji uzytkownika
}

int PQgetPrior( PQueue* pq, int i ) // zwraca priorytet informacji uzytkownika z zadanej pozycji w kolejce lub PRIOR_ERROR
{               //i to pozycja, z ktorej pobierana jest priorytet info uzytkownika
  if( PQisEmpty(pq) ) return PRIOR_ERROR; //jesli pusta
  if( i >= PQSize( pq ) || i < 0 )  return POS_ERROR; //prior w innym miejscu niz kolejka 
  return pq->pPQueue[i].nPrior; //wskaznik do elem na pozycji i w kolejce, do struktury PQItem
}

int PQFind( PQueue* pq, PQINFO* pInfo, int( __cdecl* compare )(const void*, const void*) ) // zwraca indeks wyszukiwanej informacji uzytkownika, 
//nie znana struktura informacji uzytkownika dlatego przekazac trzeba funkcje porownujaca informacje uzytkownika
// Zwaraca POS_ERROR jesli nie ma info w kolejce
{
  if( !pq ) return PRIOR_ERROR; //kolejka nie istnieje/zle zainicjowana
  if( !compare ) return POS_ERROR;    //c to funkcja porownujaca, zle jej przekazanie
  for( int i = 0; i < PQSize( pq ); i++ )
  {
    if( compare( pInfo, pq->pPQueue[i].pInfo ) == NULL ) return i; //porownuje informacje uzytkownika czy sa takie same
  }
  return POS_ERROR;
}

//POMOCNICZE!

void UpdateDown(PQItem* stog, int l, int p ) // analogicznie jak w sortowaniu stogowym ale zmienionie    
{ 
  if( l >= p ) return;      //po prostu przerobiony update z 1 projektu
  int i = l;      //indeks elem ktory przesuwamy w dol
  int j = 2 * i + 1; //indeks rodzica
  PQItem x = stog[i];
  while( j <= p ) //dopoki j>=l i priorytet j < priorytetu x 
  {
    if( j < p )
    {
      if ( stog[j].nPrior < stog[j + 1].nPrior ) j++;
    }
    if( x.nPrior >= stog[j].nPrior ) break;
    stog[i] = stog[j]; //zamianka
    i = j; //aktualizacja
    j = 2 * i + 1;
  }
  stog[i] = x;  //ustawienie na odpowiednim miejscu
}

void UpdateUp( PQItem* stog, int l, int p )// analog jak w UpdateDown, tylko uaktualnienie w gore stogu i jest tylko jeden rodzic    
{
  if( l >= p ) return;
  int i = p;
  int j = ( i - 1 ) / 2;
  PQItem x = stog[i];

  while( j >= l && x.nPrior > stog[j].nPrior )
  {
    stog[i] = stog[j];
    i = j;
    j = ( i + 1 ) / 2 - 1; //tutaj -1 bo zaczynamy od indeksu 1 i dzieki temu wrocimy do 0
  }
  stog[i] = x;
}