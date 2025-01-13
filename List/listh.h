#pragma once            //zabezpieczenie przed wielokrotnym includowaniem

#include "globalh.h"

typedef struct tagListItem      //typ uzytkownika
{
  LISTINFO* pInfo;              //wskaznik do typu zdefiniowanego przez uzytkownika
  tagListItem* pNext; //= NULL;    //nastepny element na liscie
} ListItem;



ListItem* CreateList();           //empty elem on top (GUARD)

int       Insert( ListItem* pAfter, LISTINFO* pInfo );         //insert po elemencie wskazywanym przez pAfter


LISTINFO* Remove( ListItem* pAfter );       // usun element po elemencie wsk przez pAfter
LISTINFO* Front( ListItem* pList );         // zwraca wsk do informacji pierwszego (jak top() w stosie)

int       IsEmpty( ListItem* pList );       // 1 pusta, 0 nie pusta (nie uzywac if)

void      ClearList( ListItem* pList, void( __cdecl* FreeMem )(const void*) );    //wskaznik do funkcji typu void z parametrem const void*
void      RemoveList( ListItem** pList, void( __cdecl* FreeMem )(const void*) );  //wskaznik do funkcji typu void z parametrem const void*
                                                                                   //po usunieciu ustawic liste jak NULL

void      SortList( ListItem* pList, int( __cdecl* Compare )(const void*, const void*) ); //wskaznik do funkcji z 2 parametrami const void*

ListItem* Find( ListItem* pList, LISTINFO* pItem, ListItem** pPrev, int( __cdecl* Compare )(const void*, const void*) ); //return int value