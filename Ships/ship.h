#ifndef SHIP_H
#define SHIP_H



int move( int** pTab, int nRow, int nCol, int nDepth, int moving, int x, int y, int* px, int* py, int** pRoot );
/* pTab - tablica okreslajaca glebokosc w kazdym kwadracie
   nRow, nCol - rozmiar pTab,
   nDepth - minimalna glebokosc aby statek przeplynal
   moving - kierunek ruchu (wart typu wylicz)
   x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
   px, py - adresy nowych wspolrzednych  (parametry WY)
   pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/


int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );  // rekurencyja
/* pTab tabl glebokosci   o romiarze nRow  i nCol
    dDepth - glebokosc zanurzenia statku
    x, y - wspolrzedne skad robimy kolejny ruch
    pRoot tablica kolejnych ruchow (w pole wstawia sie numer kolejnego ruchu)
    x_dest, y_dest - wsporzedne portu
*/

//int** createTab1( int nRow, int nCol );
//int** createTab2( int nRow, int nCol ); //inna metoda (N*M)

void clearRoot( int** pRoot, int nRow, int nCol ); //zerowanie tablicy
int setTab( char* sFile, int** pTab, int nRow, int nCol ); //wczytywanie danych z pliku


#endif