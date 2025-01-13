#include "listh.h"
#include <stdlib.h>
#include <stdio.h>


ListItem* CreateList()
{
	return (ListItem*)calloc( 1, sizeof( ListItem ) ); //calloc w odroznieniu od malloc samoistnie =NULL
}

int IsEmpty( ListItem* pList )
{
  return !pList || !pList->pNext;
  //jesli glowa jest zerem lub 1 elem zerem
  // 1 jest pusta, 0 nie pusta
}

void SortList( ListItem* pList, int( __cdecl* Compare )(const void*, const void*) )
{
    //pNext to nast elem listy, pCurr to aktualny elem
  if( !Compare ) //dopoki pusta
  {
    perror( "Error in &Compare" );
    return;
  }
    ListItem* pFirst = pList;  //pList to glowa listy, pierwszy elem

    while( !IsEmpty( pFirst ) ) //dopoki lista sie nie skonczy
    {
      ListItem* pMin = pFirst;    //pierwszy jest najmniejszy
      ListItem* pCurr = pFirst->pNext; //teraz "pierwszym jest nastÍpny"

      while( !IsEmpty( pCurr ) )  //dopoki nie wyjdzie poza liste
      {
        if( comp( pMin->pNext->pInfo,pCurr->pNext->pInfo ) == 1 ) //jesli pCurr jest mniejsze to zwraca 1 i znalezione nowe min
          pMin = pCurr;

        pCurr = pCurr->pNext; //przeskakujemy na kolejny elem listy
      }
      if( pMin != pFirst )   //czy min nie jest g≥owπ
      {
        pCurr = pMin->pNext->pNext;     //przesuniecie o 2 miejsca po min
        pMin->pNext->pNext = pFirst->pNext; //min to teraz 1 elem listy
        pFirst->pNext = pMin->pNext;      //wycina pMin z listy i wstawia go za pFirst
        pMin->pNext = pCurr;              //reszta listy ktÛra byla po min elem
      }
      pFirst = pFirst->pNext;  //przesuniecie z 1 elem, zaczynamy od poczatku az sie posortuje
    }
}

int Insert( ListItem* pAfter, LISTINFO* pInfo ) //przypadek 3
{
  if( !pAfter ) return 0; //pAfter to elem po tym do ktorego chcemy wstawic
  ListItem* pNew = (ListItem*)calloc( 1, sizeof( ListItem ) ); //alokacja na nowy elem listy
  if( pNew == NULL )  return 0;
  pNew->pInfo = pInfo; //wype≥nienie informacji w nowym elemencie (w prezentacji pNew->nKey = x)

  pNew->pNext = pAfter->pNext; //przypisanie na nastÍpny elem do nowego (w prezentacji pAfter to v)
  pAfter->pNext = pNew; //przypisanie nowego elem jako nastÍpnik v

  return 1;
}

LISTINFO* Remove( ListItem* pAfter )//usuwanie elem
{
  if( IsEmpty( pAfter ) ) return NULL;  //jesli puste to nie ma co usuwac
  // v i p w prezentacji
  ListItem* pNew = pAfter->pNext; //wskazuje na nastÍpnik pAfter, czyli ten element, ktÛry ma byÊ usuniÍty
  pAfter->pNext = pNew->pNext; //laczenie pAfter z kolejnym elem 
  LISTINFO* pInfo = pNew->pInfo; //przechowanie przed zwolnieniem pamiÍci
  free( pNew ); //zwalnia pNew, usuwujac go z listy

  return pInfo; //pInfo reprezentuje usuniÍtπ informacjÍ ( zeby moøna bylo zrobiÊ cos jeszcze na tej informacji)
}

LISTINFO* Front(ListItem* pList)   //zwracanie pierwszego elem
{                           //zwraca pList->pNext->pInfo, ale nigdzie nie uzylam takiego zwrotu, wiec jej rowniez nie uzylam, ale jest w szkicu, wiec zostawiam 
    return ( IsEmpty(pList) ) ? NULL : pList->pNext->pInfo;//przypisanie wskaünika na pierwszy elem i odczytanie info z pierwszego elem
                                                            //zwrÛcenie informacji z pierwszego elementu listy
}

void ClearList( ListItem* pList, void( __cdecl* FreeMem )(const void*) )   //usuwa wszystkie elementy z listy i zwalnia zajmowanπ przez nie pamiÍÊ
{
  if( !pList && !FreeMem )
  {
    perror( "List is empty or Error in FreeMem!\n" );
    return;
  }
    while(!IsEmpty( pList ))//dopoki lista nie jest pusta
    {
      freemem( Remove( pList ) );//zwolnienie
    }
}

void RemoveList( ListItem** pList, void( __cdecl* FreeMem )(const void*) )  //usuwa calkowicie liste ≥πcznie z g≥owπ (po usunieciu ustawic liste jak NULL)
{
  if( !pList ||  !*pList )
  {
    perror( "Error in *pList!\n" );
    return;
  }

    ClearList( *pList, freemem ); //usuniecie i zwolnienie wszystkich elem
    free( *pList );   //zwolnienie pamieci glowy
    *pList = NULL;    //lista to NULL
}

ListItem* Find( ListItem* pList, LISTINFO* pItem, ListItem** pPrev, int( __cdecl* Compare )(const void*, const void*) ) //szukanie konkretnego elem
{
  if( !Compare )  return *pPrev = NULL;
  
  *pPrev = pList; // elem na g≥owÍ listy
   while( !IsEmpty( *pPrev ) ) //dopoki nie zero (czyli jesli wyjdzie to znaczy ze nie znalazlo szukanego elem)
   {
     ListItem* now = (*pPrev)->pNext; //przesuniecie na nast elem
     if( !Compare(pItem, now->pInfo) ) return now;  //porownywanie zeby znalezc, jesli tak zwracamy wskaünik na ten element 
     *pPrev = now;        //pPrev na bieøπcy element
   }   
    return *pPrev = NULL;      //nie znalazlo, ustawiamy *pPrev na NULL i zwracamy NULL
}