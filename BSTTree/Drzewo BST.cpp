#include "tree.h"

int main( int argc, char* argv[] ) 
{
  if( argc != 2 ) 
  {
    printf( "Usage: %s <filename>\n", argv[0] );
    return -1;
  }
  FILE* infile = fopen( argv[1], "r"); // r oznacza ze plik jest tylko do odczytu, argv przechowuje plik
  if( !infile ) 
  {
    printf( "Cannot open the file %s!!\n", argv[1] );
    return -2;
  }
  TreeItem* root = NULL;

  CountLetters( infile, &root );

  fclose( infile ); //zamykamy plik wejsciowy

  FILE* file = fopen( "Slownik.txt", "w" );  //w oznacza plik do zapisu
  if( !file ) 
  {
     perror( "Nie mozna zapisac pliku!\n" );
     free( root );
     return -3;
  }
 
  inOrderPrint( root );
  inOrderToFile( root, file );

  fclose( file );

  FreeTree( root );
  return 0;
}