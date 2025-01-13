#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Numery linii są zapamiętane w kolejności rosnącej w liście prostej( ListItem )
typedef struct ListItem //do przechowywania numerow linii w ktorych wystepuje slowo
{
  int storeline; //przechowuje linie
  ListItem* pNext; //nastepny element listy
} ListItem;

//z podwójną głową( nowy typ strukturalny - ListHead dla głowy listy - pFirst, pLast )
typedef struct ListHead //koniec i poczatek listy zeby mozna bylo operowac z dwoch stron (tak rozumiem zamysł listy z dwiema głowami?)
{
  ListItem* pFirst; //pierwszy element listy
  ListItem* pLast; //ostatni element listy
} ListHead;

/*Zdefiniować strukturę danych dla elementu drzewa BST(TreeItem), w ktorym
jest przechowywane słowo, ilość wystąpień oraz numery linii( nie powtarzajace sie ).
Słowo jest tablicą  dynamiczną( pWord )*/
typedef struct tagTreeItem
{
  char* pWord; //tablica dynamiczna dla slow
  int i;       //ilosc wystapien
  ListHead newline; //numery linii
  tagTreeItem* right; //prawe poddrzewo wezla, alfabetycznie wieksze
  tagTreeItem* left; //lewe, mniejsze
} TreeItem;


TreeItem* Create( const char* word, int line );
void Insert( TreeItem** root, char* word, int line );
void inOrderToFile( TreeItem* pRoot, FILE* file );
void FreeTree( TreeItem* pRoot );
void CountLetters( FILE* infile, TreeItem** pRoot );
void inOrderPrint( TreeItem* pRoot ); //DO TESTU ZAPISU
void Visit( TreeItem* pRoot, int line );
