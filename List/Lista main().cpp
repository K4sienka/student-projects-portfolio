#include "listh.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG //warunkowe drukowanie
#define ITEM 20 //ilosc elementow
#define SEEKED 2000 //szukany elem
#define INPUT 3000 //elem do wstawienia
#define MAX 50 //max wartość klucza

void Print( ListItem* pList );
LISTINFO* Create( int nKey, int n ); //pomocnicza żeby nie zawalic main

/*W programie głównym należy:
 dodać minimum 20 elementów z kluczami losowymi (<50) (nKey) a do pierwszego elementu
dynamicznej tablicy dwuelementowej wstawiać indeks pętli (dla indeksu 9 wstawić klucz 2000)
 posortować,
 wyszukać element z kluczem 2000,
 wstawić przed znalezionym, element z kluczem 3000
 usunąć element z kluczem 2000
 zwolnić listę
 wstawić dwa elementy
 Usunąć całą listę
 Napisać funkcję drukującą info (klucze) z listy i po każdej operacji drukować listę*/

int main()
{			
	ListItem* pList = CreateList();				//tworzenie pustej listy
	if(!pList )
	{
		perror( "Error in creating pList!\n" );
		return -1;
	}

	srand( (unsigned int)time(NULL) );//losowe elementy
for( int i = 0; i < ITEM; i++ )
{
	int key = 0;
	if( i == 9 ) key = 2000; //2000 dla indeksu 9
	else key = rand() % MAX; //dla innych random

	int indeks = i;
	LISTINFO* x = Create(key, indeks); //stworz liste
	if(!x)
	{
		perror( "Error in creating x!\n" );
		return -2;
	}
	if( !Insert(pList, x) )
	{
		perror( "Error in adding new element 0!" );
		freemem( x );
		return -3;
	}
}

#ifdef DEBUG
	printf( "Wygenerowana lista\n" );
	Print( pList );
#endif

	SortList( pList, comp );

#ifdef DEBUG
	printf( "Posortowana lista\n" );
	Print( pList );
#endif

	LISTINFO* seek = Create( SEEKED, NULL );
	if( !seek )
	{
		perror( "Error in searching!" );
		return -4;
	}
	ListItem* pPrev = NULL;			//poprzedni element
	ListItem* Look = Find( pList, seek, &pPrev, comp ); //pList to wskaznik na liste, seek to obiekt ktorego szukamy, pPrev to adres poprzedniego elem, comp porownuje klucze
	if(Look)
	{
		if(Look->pInfo) printf( "Znaleziony element ma klucz: %d\n", Look->pInfo->nKey );

		if(pPrev->pInfo)
		{
			printf( "Klucz poprzedniego elementu: %d\n", pPrev->pInfo->nKey );
		}
		else printf( "Znaleziony element jest pierwszy (nie ma poprzednika)\n" );
	}

	freemem( seek ); //zwolnienie pamięci dla szukanego

	LISTINFO* In = Create( INPUT, ITEM + 1 ); //wstawic nowy element przed szukanym o wartosci 3000, dlatego trzeba dac +1
	if( !In )
	{
		perror( "Error in creating new item (In)" );
		return -5;
	}
	if( !Insert( pPrev, In ) )
	{
		perror( "Error in adding new element 1!" );
		freemem( In );
		return -6;
	}

	printf( "Lista z wstawionym elementem \n" );
	Print( pList );

	seek = Remove( pPrev->pNext ); //usunac znaleziony wczesniej elem, pPrev->pNext to tutaj nasz item do usuniecia
	if( !seek )
	{
		perror( "Error in removing seek!" );
		return -7;
	}

#ifdef DEBUG
	printf( "Lista z usunietym elementem\n" );
	Print( pList );
#endif
	freemem( seek );	//zwolnic pamiec po usunieciu (inaczej seek nadal posiadalby informacje o usunietym elem)
	ClearList( pList, freemem );	//zwolnic liste

	seek = Create( 33, 4 );			//33 to nowy element do wstawienia, 4 to indeks
	if( !seek )
	{
		perror( "Error in creating seek!" );
		return -8;
	}
	if( !Insert( pList, seek ) )
	{
		perror( "Error in adding new element 2!" ); //nie udalo sie wstawic 22
		freemem( seek );
		return -2;
	}
	seek = Create( 22, 3 );		//22 to nowy element do wstawienia, 3 to indeks
	if( !Insert( pList, seek ) )
	{
		perror( "Error in adding new element 3!" ); //nie udalo sie wstawic 33
		freemem( seek );
		return -3;
	}

	printf( "Dodane nowe elementy\n" );
	Print( pList );
	
	RemoveList( &pList, freemem );		//usunąć całą liste
	printf( "Usunieta lista:\n" );
	Print( pList );

	return 0;
}

int comp( const void* a, const void* b ) //porównuje dwie pozycje z listy
{ 
	if( (( LISTINFO* )a)->nKey > (( LISTINFO* )b)->nKey ) return 1;		//1 jeśli pierwszy jest wiekszy niz drugi
  if( (( LISTINFO* )a)->nKey < (( LISTINFO* )b)->nKey ) return -1;	//zwraca -1 jeśli pierwszy jest mniejszy niż drugi
	return 0;																													//0 jesli sa rowne (musi tak byc bo z 3 ifami bylo ostrzeżenie, jeśli nie spelni żaden if zadanego warunku)
}

void freemem( const void* p )   //zwalnia pamiec
{
  free( (( LISTINFO* )p)->pTab );  //wskaznik do struktury LISTINFO, zwolnienie pTab
  free( (LISTINFO*)p );     //zwolnienie struktury
}


LISTINFO* Create( int nKey, int n )
{
	LISTINFO* a = ( LISTINFO* )calloc( 1, sizeof( LISTINFO ) ); //alokacja pamieci
	if(a == NULL)		return NULL;
	a->nKey = nKey;
	a->pTab = (int*)calloc( 2, sizeof( int ) ); //2 bo rozmiar tablicy taki ma byc
	if( a->pTab == NULL )
	{
		free( a ); //zwolnic pamiec
		return NULL;
	}
	a->pTab[0] = n;
	a->pTab[1] = NULL;
	return a; //zwroc nowy element
}


void Print( ListItem* pList ) //Napisać funkcję drukującą info (klucze) z listy
{
		if ( IsEmpty(pList) )		return;
	
		ListItem* x = pList; //zaczynamy od glowy
		int i = 1;					//zaczynamy od indeksu 1
		while( !IsEmpty( x ) ) //dopoki nie skoncza sie elem
		{
			x = x->pNext; //przesuwamy 
			printf( "Element %d = %d oraz pTab[0]= %d\n", i, x->pInfo->nKey, x->pInfo->pTab[0] ); //i to numer drukowanego itemu, a x to wartosc aktualnego klucza
			i++;
		}
}