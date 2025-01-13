#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "PQueue.h"

/*INSTRUKCJE
- wykreowac kolejke FMAX - sto elementowa
- dodac 6 elementow z roznymi priorytetami i w ró¿nej kolejnosci priorytetów - wydrukowac
- usunac z kolejki( z najwiekszym priorytetem ) - wydrukowac
- dodac dwa elementy - wydrukowac
- wyszukac jeden elem
- zwiekszyc mu priorytet( unikalny ) - wydrukowac
- zmniejszyc priorytet innemu elementowi( unikalny ) - wydrukowac
- usuac cala kolejke


- Operacja usuwania z kolejki polega na usunieciu pierwszego (zerowego) elementu z kolejki,
	 zmniejszaj¹c ilosc elementow w kolejce oraz nastepnie wkopiowac ostatni z kolejki w pierwsza pozycje
	 i przywrocic warunken stogu metoda UpdateDown() z sortowania (zmodyfikowana jak do
	 sortowania malejacego - bo prioprytety od najwiekszego  do najmniejszego)

 - Operacja  dodania nowego elementu -> dodajemy na koncu, zwiêkszaj¹c ilosc elementow w kolejce
	 i uaktualniamy stog ale od dolu do gory- UpdateUp (podobnie jak w dol ale latwiej bo jest tylko jeden rodzic)

 - zdefiniowaæ podobnie jak w przypadku FIFO oraz modulu Listy plik global.h z deklaracja typu
	 definiowanego przez uzytkownika (jaka informacja bedzie przechowywana w kolejce)
	 Prosze tu uzyc tego samego typu co w poprzendich projektach (struktura zalozona z int-a oraz wsk na int
	 czyli tablicy dynamicznej int-ow)
*/

#define SIZE 20 //tyle ma miec miejsca
#define ELEM 6 //tyle dodac na poczatku elementow
#define PMAX 100 //maksymalna wartosc priorytetu
#define KMAX 20 //maksymalna wartosc klucza
#define FMAX 30 //maksymalna wartosc 1-ego elementu
#define ADD ELEM + 2//do dodawania elementow
#define PRIORCHANGE 200 // do zmiany priorytetów

#define DEBUG
//#define TEST

void PrintQueue( const void* pTab );
PQINFO* CreateInfo();


int comp( const void* a, const void* b );
void freemem( const void* p );

int main()
{
	srand( ( unsigned int ) time( NULL ) );
	PQueue* queue = PQCreate( SIZE ); //- wykreowac kolejke 20 - sto elementowa
	if( queue == NULL )
	{
		perror( "Error with creating a queue\n" );
		return -1111;
	}
	for(int j = 0; j < ELEM; j++)
	{
		PQINFO* pInfo = CreateInfo();
		if(!pInfo) 
		{
			perror( "Error in Creating\n" );
			return -10;
		}
		pInfo->Key = rand() % KMAX;
		pInfo->pTab[0] = rand() % FMAX;  // Przypisanie kolejnych wartoœci od 0 do 19
		if(!PQEnqueue( queue, pInfo, rand() % PMAX ))
		{
			perror( "Error in PQEnqueue\n" );
			return -11;
		}
	}

	printf( "Kolejka prior z %d losowymi wartosciami:\n", ELEM ); //- dodac 6 elementow z roznymi priorytetami i w ró¿nej kolejnosci priorytetów - wydrukowac
	PQPrint( queue, 0, PrintQueue );

	PQINFO* r = PQDequeue( queue );
	if(!r)
	{
		printf( "Queue is empty!\n" );
		return -22;
	}
	else
	{
		printf( "\nKlucz usunietego elementu: %d \n", r->Key );
		freemem( r );
	}

#ifdef DEBUG
	printf( "\nKolejka po usunieciu elementu:\n" );
	PQPrint( queue, 0, PrintQueue );
#endif
	//printf( "\nUsuniety element o indeksie 0 i najwiekszym priorytecie:\n" ); //- usunac z kolejki( z najwiekszym priorytetem ) - wydrukowac
	//PrintQueue( r );

	for(int z = ELEM; z <= ADD; z++)
	{
		PQINFO* pInfo = CreateInfo();
		if(!pInfo)
		{
			perror( "Error in Creating\n" );
			return -12;
		}
		pInfo->Key = rand() % KMAX;
		pInfo->pTab[0] = rand() % FMAX;
		if(!PQEnqueue( queue, pInfo, rand() % PMAX ))//-dodac dwa elementy - wydrukowac
		{
			perror( "Error in PQEnqueue\n" );
			return -16;
		}
	}
	printf( "\n\nKolejka prior z %d elementami po dodaniu:\n", ADD );
	PQPrint( queue, 0, PrintQueue );

	PQINFO* pInfo1 = CreateInfo();
	if(!pInfo1)
	{
		perror( "Error in Creating\n" );
		return -13;
	}
	pInfo1->Key = 22;
	pInfo1->pTab[0] = rand() % FMAX;
	if(!PQEnqueue( queue, pInfo1, 100 ))
	{
		perror( "Error in Creating\n" );
		return -17;
	}
	PQINFO* pInfo2 = CreateInfo();
	if(!pInfo2)
	{
		perror( "Error in Creating\n" );
		return -14;
	}
	pInfo2->Key = 33;
	pInfo2->pTab[0] = rand() % FMAX;
	if(!PQEnqueue( queue, pInfo2, 80 ))
	{
		perror( "Error in Creating\n" );
		return -18;
	}
	printf( "\nDodanie elementu o kluczu 22 i 33 do wyszukania:\n" );
	PQPrint( queue, 0, PrintQueue );

	int Key1 = PQFind( queue, pInfo1, comp ); //- wyszukac jeden elem 
	if(Key1 == PRIOR_ERROR || Key1 == POS_ERROR)
	{
		printf( "Error in Key1" );
	}

	if( PQsetPrior( queue, Key1, 100 + PRIORCHANGE ) == PRIOR_ERROR ) //- zwiekszyc mu priorytet( unikalny ) - wydrukowac
	{
		perror( "Error in Set1\n" );
	}
	int Key2 = PQFind( queue, pInfo2, comp );
	if(Key2 == PRIOR_ERROR || Key1 == POS_ERROR)
	{
		printf( "Error in Key2" );
	}
	if( PQsetPrior( queue, Key2, 80 - PRIORCHANGE )== PRIOR_ERROR ) //- zmniejszyc priorytet innemu elementowi( unikalny ) - wydrukowac
	{
		perror( "Error in Set2\n" );
	}

#ifdef DEBUG
	printf( "\nZwiekszenie priorytetu dla kluczu 22 i zmniejszenie priorytetu dla kluczu 33:\n" );
	PQPrint( queue, 0, PrintQueue );
#endif
	
	PQRelease( &queue, freemem );

#ifdef TEST
	srand( ( unsigned int )time( NULL ) );
	PQueue* Tqueue = PQCreate( SIZE );

	PQINFO* Item1 = CreateInfo();
	Item1->Key = rand() % KMAX;
	Item1->pTab[0] = rand() % FMAX;
	PQEnqueue( Tqueue, Item1, 4 );

	PQINFO* Item2 = CreateInfo();
	Item2->Key = rand() % KMAX;
	Item2->pTab[0] = rand() % FMAX;
	PQEnqueue( Tqueue, Item2, 11 );

	PQINFO* Item3 = CreateInfo();
	Item3->Key = rand() % KMAX;
	Item3->pTab[0] = rand() % FMAX;
	PQEnqueue( Tqueue, Item3, 11 );

	PQINFO* Item4 = CreateInfo();
	Item4->Key = rand() % KMAX;
	Item4->pTab[0] = rand() % FMAX;
	PQEnqueue( Tqueue, Item4, 9 );

	printf( "\n\nTEST! Kolejka prior z losowymi wartosciami:\n" );
	PQPrint( Tqueue, 0, PrintQueue );

	PQINFO* b = PQDequeue( Tqueue );
	printf( "\nKolejka po usunieciu elementu:\n" );
	PQPrint( Tqueue, 0, PrintQueue );
	printf( "\nUsuniety element o indeksie 0 i najwiekszym priorytecie:\n" );
	PrintQueue( b );
	
#endif

	return 0;
}

int comp( const void* a, const void* b )    //JAK Z LISTY
//porównuje dwie pozycje z listy
{
	if( (( PQINFO* )a)->Key > (( PQINFO* )b)->Key ) return 1;		//1 jeœli pierwszy jest wiekszy niz drugi
	if( (( PQINFO* )a)->Key < (( PQINFO* )b)->Key ) return -1;	//zwraca -1 jeœli pierwszy jest mniejszy ni¿ drugi
	return 0;																													//0 jesli sa rowne (musi tak byc bo z 3 ifami bylo ostrze¿enie, jeœli nie spelni ¿aden if zadanego warunku)
}

void freemem( const void* p )   //JAK Z LISTY
//zwalnia pamiec
{
	//int* f = (( PQINFO* )p)->pTab; //wskaznik do struktury PQINFO
	//free( f );                //zwolnienie pTab
	//free( ( PQINFO* )p );//zwolnienie struktury
	free( ( ( PQINFO* ) p )->pTab );
	free( ( PQINFO* ) p );
}

void PrintQueue( const void* pTab ) 
{
	PQINFO* q = ( PQINFO* )pTab;
	printf( " Klucz: %d; Pierwszy element: %d; ", q->Key, q->pTab[0] );
}

PQINFO* CreateInfo() 
{
	PQINFO* q = ( PQINFO* )calloc( 1, sizeof( PQINFO ) );
	if( q )
	{
		q->pTab = ( int* )calloc( 2, sizeof( int ) );
		if( !(q->pTab) ) return NULL;
		return q;
	}
	else return NULL;
}
