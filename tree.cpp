#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10 //do max ilosci liter

int StrCmp( char* s1, char* s2 );

int IsDigit( char c );
char* Realloc( char* c );
int IsLetter( char c );
int IsAlpha( char c );


int StrCmp( char* s1, char* s2 )  // wskazujemy na tablice znakow, tutaj stringi
{
  char* x = ( char* ) calloc( strlen( s1 ) + 1, sizeof( char ) );// +1 bo jet znacznik konca
  if( x == NULL ) return NULL;
  char* y = ( char* ) calloc( strlen( s2 ) + 1, sizeof( char ) );
  if( y == NULL ) return NULL;
  strcpy( x, s1 );  // s1 do kopii, strcpy kopiuje lancuch znakow do tablicy znakow
  strcpy( y, s2 );  // s2 do kopii
  x = _strupr( x ); // zamiana obydwu kopii lancuchow na duze litery
  y = _strupr( y );
  // x = _strlwr( x ); // zamiana obydwu kopii lancuchow na male litery
  // y = _strlwr( y );
  int compare = strcmp( x, y );  // porownanie tych kopii

  free( x );  // zwolnienie 2x
  free( y );

  return compare;  // zwrocenie porownania ( pozniej inorder posortuje )
}

TreeItem* Create( const char* word, int line ) // do przechowywania slow, liczby ich wystapien i ich linii
{
  TreeItem* node = ( TreeItem* )calloc( 1, sizeof( TreeItem ) ); // alokacja pamieci dla nowego wezla
  if( !node ) 
  {
    perror( "Memory allocation error (node)!\n" );
    return NULL;
  }

  node->pWord = ( char* ) calloc ( strlen( word ) + 1, sizeof( char ) );// do przechowania pamieci kopii
  if( !(node->pWord) ) 
  {
    perror( "Error in coping the word!\n" );
    return NULL;
  }
  strcpy( node->pWord, word ); // trzeba skopiowac slowo zeby zachowac niezmiennosc danych w drzewie
  node->i = 1; // 1 czyli pierwsze wystapienie slowa

  node->newline.pFirst = ( ListItem* )calloc( 1, sizeof( ListItem ) ); // lista o dwoch glowach ( na pierwszy i ostatni elem )
  if( !(node->newline.pFirst) ) 
  {
    perror( "Error in allocating new line!\n" );
    return NULL;
  }
  
  node->newline.pFirst = ( ListItem* )calloc( 1, sizeof( ListItem ) ); // alokacja na pierwsze slowo

  if( !( node->newline.pFirst) )
  {
    perror( "Error in allocating first item!\n" );
    return NULL;
  }

  node->newline.pFirst->storeline = line; // numer linii do pierwszego elem aby sledzic numer linii wystapienia slowa
  node->newline.pLast = node->newline.pFirst; // na poczatku 1 elem dlatego poczatek i koniec w tym samym miejscu, potem stopniowo dodaje sie elem i wszystko sie przesuwa
  return node; // dzieki temu dolacza sie wezel do drzewa i mozna przeprowadzac na nim rozne operacje
}

void Insert( TreeItem** pRoot, char* word, int line ) // wstawianie nowego slowa do drzewa
{
  if( !(*pRoot) ) // Drzewo jest puste, tworzymy nowy wezel
  {
    *pRoot = Create( word, line );
    return;
  }

  int compare = StrCmp( word, ( *pRoot )->pWord ); // porownujemy slowa i wartosc compare wyrzuca nam: >0 jesli wyraz jest wiekszy ( alfabetycznie )
                                              // 0> jesli wyraz jest mniejszy i 0 jesli sa takie same
  if( compare > 0 )  Insert( &( ( *pRoot )->right ), word, line ); // wieksze wiec lecimy do prawego poddrzewa
  else if( compare < 0 )  Insert( &( ( *pRoot )->left ), word, line ); // mniejsze, do lewego
  else Visit( *pRoot, line ); // takie samo slowo

  /*{ 
    ( *pRoot )->i++; // aktualizujemy liczbe wystapien i numer linii

  
    ListItem* item = ( ListItem* ) calloc( 1, sizeof( ListItem ) );  // nowy element listy
    if( !item ) 
    {
      perror( "Error in memory allocation (item)!\n" );
      return;
    }
    item->storeline = line; // wartosc na nr linii

    ( *pRoot )->newline.pLast->pNext = item; // nowy element na koniec listy
    ( *pRoot )->newline.pLast = item; 
  }*/
}

void inOrderToFile(TreeItem* pRoot, FILE* file)
{
  if( !pRoot )  return;
  inOrderToFile( pRoot->left, file ); // rekurencyjnie lewe

  fprintf( file, "%s: \nIlosc wystapien slowa: %d; \n", pRoot->pWord, pRoot->i ); // slowo i ilosc wystapien

  ListItem* now = pRoot->newline.pFirst; // biezacy element listy
  fprintf( file, "Numer linii jego wystapienia:" );

  int prev = -1; // zeby przechowac poprzedni nr linii
  while( now != NULL ) // dopoki lista sie nie skonczy
  {
    if( now->storeline != prev ) // jesli aktualna nowa linie =/= poprzedniej
    {
      if( prev != -1) fprintf( file, "," ); // zeby przecinki bezsensu sie nie drukowaly dla tych samych linii
      fprintf( file, " %d", now->storeline ); // drukowanie numeru linii
      prev = now->storeline; // przesuniecie prev
    }
    now = now->pNext; // przesuniecie now
  }
  fprintf( file, ";\n\n" );
  inOrderToFile( pRoot->right, file ); // rekurencyjnie prawe
}

void FreeTree( TreeItem* pRoot ) // zwolnienie pamieci w kolejnosci PostOrder
{
  if( !pRoot ) return;
  FreeTree( pRoot->left ); // zwolnic lewe poddrzewo
  FreeTree( pRoot->right ); // zwolnic prawe poddrzewo
  free( pRoot );
}


void CountLetters( FILE* infile, TreeItem** pRoot )
{
  char* word = ( char* ) calloc( MAX, sizeof( char ) ); // alokacja pamieci dla slowa
  int line = 1;
  int i = 0;
  int size = MAX;
  int current;

  while(( current = fgetc( infile ) ) != EOF) // czytanie pliku znak po znaku
  { 
    if( !IsAlpha( current )) // jesli nie ma zadnego separatora
    {
      if( i > 0 )
      {
        word[i] = '\0'; // znak 0 jako koniec wyrazu
        if( !IsDigit(word[0]) ) Insert( pRoot, word, line ); // dodaj do drzewa
        i = 0; // koniec slowa, indeksowanie zaczynamy od zera
      }
      if(current == '\n')  line++; // jesli jest nowa linia to zwiekszamy znacznik
    }
    else
    {
      if( i == 9 )  word = Realloc( word ); // jesli dojdziemy do 10 to realloc
      word[i] = current; // odczytany znak to teraz indeks tablicy
      i++; // kolejny znak 
    }
  }
    if( i > 0 ) // zakonczenie odczytu pliku ale trzeba dodac ostatnie slowo
    {
     word[i] = '\0';
     if( i == 9 )
     {
       word = Realloc( word );
     }
      if ( !IsDigit(word[0]) ) Insert( pRoot, word, line );
    }
   free( word ); // zwolnienie pamieci dla word
}


void Visit( TreeItem* pRoot, int line )
{
  pRoot->i++;

  if(line == pRoot->newline.pLast->storeline) return; // wywalanie powtorzen

  ListItem* item = ( ListItem* ) calloc( 1, sizeof( ListItem ) ); // nowy elem listy
  if( !item ) 
  {
    perror( "Error in memory allocation (item)!" );
    return;
  }
  item->storeline = line;   // wartosc na nr linii
  pRoot->newline.pLast->pNext = item; // nowy element na koniec listy
  pRoot->newline.pLast = item;
}

int IsDigit( char c )
{
  return ( c >= '0' && c <= '9' );
}

int IsLetter( char c )
{
  return ( c >= 'A' ) && ( c <= 'Z' ) || ( c >= 'a' ) && ( c <= 'z' ) || ( c == '_' );
}

int IsAlpha( char c )
{
  return IsLetter( c ) || IsDigit( c );
}

char* Realloc ( char* c )
{
  char* newword = ( char*) realloc( c, 20 * sizeof( char ) ); // realokacja dla wyrazu wiecej niz 10
  if( c ) // c wskazuje na ciag znakow
  {
    memset( c + 10 , 0, 10 * sizeof( char ) ); // wypelnienie pamieci 0
    c = newword; // zachowanie oryginalu
    return c;
  }
  return NULL; // w przypadku bledu alokacji
}

void inOrderPrint( TreeItem* pRoot )
{
  if(!pRoot)  return;
  inOrderPrint( pRoot->left ); // rekurencyjnie lewe

  printf( "%s: \nIlosc wystapien slowa: %d; \n", pRoot->pWord, pRoot->i ); // slowo i ilosc wystapien

  ListItem* now = pRoot->newline.pFirst; // biezacy element listy
  printf( "Numer linii jego wystapienia:" );

  int prev = -1; // zeby przechowac poprzedni nr linii
  while(now != NULL) // dopoki lista sie nie skonczy
  {
    if(now->storeline != prev) // jesli aktualna nowa linie =/= poprzedniej
    {
      if(prev != -1) printf( "," ); // zeby przecinki bezsensu sie nie drukowaly dla tych samych linii
      printf( " %d", now->storeline ); // drukowanie numeru linii
      prev = now->storeline; // przesuniecie prev
    }
    now = now->pNext; // przesuniecie now
  }
  printf( ";\n\n" );
  inOrderPrint( pRoot->right ); // rekurencyjnie prawe
}


/*
  size += 10; // zwiekszenie o 10
        char* newword = ( char* )realloc( word, size * sizeof(char) );
        if( !newword )
        {
          printf( "Error in reallocation for newword!\n" );
          free( word ); //zwolnienie pamieci przed zakonczeniem programu
          return;
        }
        memset( word + ( size - 10 ), 0, MAX * sizeof( char ) ); // wypelnienie ostatnich 10 bajtow zerami
        word=newword;
}*/

/*void CountLetters(FILE* infile, TreeItem** pRoot)
{
  char* word = ( char* ) calloc( MAX, sizeof( char ) ); // slowo ma miec max 10 znakow, dla wiekszej ma byc funkcja realloc, uzywam dynamicznego alokowania pamieci zeby moc zmieniac "pojemnosc"
  if(!word)
  {
    perror( "Allocation memory error!\n" );
    return;
  }

  int line = 1; // zaczynamy od linii 1
  int i = 0; // do sledzenia indeksu tablicy
  int size = MAX; // aktualny rozmiar slowa

  while(!feof( infile )) // feof uzywamy aby sledzic koniec pliku
  {
    char current = fgetc( infile ); // przypisanie aktualnego slowa (fgetc odczytuje jeden znak z wskazanego strumienia, tutaj:pliku wejsciowego)
    if(current == ' ' || current == '\t' || current == '\n') // sprawdzanie odstepu i nowej linii
    {
      if(i > 0) // zapisane poprzednie slowo w tablicy, wiec dodajemy do drzewa
      {
        word[i] = '\0'; // ostatni znak slowa na 0, czyli jego koniec
        if(!IsDigit( word[0] )) // pomijanie slow rozpoczynajacych sie od liczb
        {
          Insert( pRoot, word, line ); // dodajemy do drzewa
        }
        i = 0; // i na 0 zeby tworzyc kolejne slowa
      }
      if(current == '\n')
      {
        line++; // nowa linia znaleziona, wiec idziemy dalej
      }
    }
    else
    {
      if(i >= size) // spr czy potrzebna realokacja
      {
        word = Realloc( word );
      }
      word[i] = current; // znalezione slowo wiec zwiekszamy az nie dojdzie do jakies linii/odstepu i wtedy go wyzej dodajemy do drzewa
      i++;
    }
  }
  if(i > 0) // dla ostatniego slowa zeby tez sie dodalo do drzewa
  {
    word[i] = '\0';
    Insert( pRoot, word, line );
    line++;
  }
  free( word ); // zwolnienie pamieci po zakonczeniu funkcji
}*/