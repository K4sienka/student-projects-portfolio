#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Numery linii s� zapami�tane w kolejno�ci rosn�cej w li�cie prostej( ListItem )
typedef struct ListItem //do przechowywania numerow linii w ktorych wystepuje slowo
{
  int storeline; //przechowuje linie
  ListItem* pNext; //nastepny element listy
} ListItem;

//z podw�jn� g�ow�( nowy typ strukturalny - ListHead dla g�owy listy - pFirst, pLast )
typedef struct ListHead //koniec i poczatek listy zeby mozna bylo operowac z dwoch stron (tak rozumiem zamys� listy z dwiema g�owami?)
{
  ListItem* pFirst; //pierwszy element listy
  ListItem* pLast; //ostatni element listy
} ListHead;

/*Zdefiniowa� struktur� danych dla elementu drzewa BST(TreeItem), w ktorym
jest przechowywane s�owo, ilo�� wyst�pie� oraz numery linii( nie powtarzajace sie ).
S�owo jest tablic�  dynamiczn�( pWord )*/
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