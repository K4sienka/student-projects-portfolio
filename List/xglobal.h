//ZABEZPIECZYC PREPROCESOREM PRZED WIELOKROTNYM INKLUDOWANIEM !!!!

/*--------------------------------------------------------------
* Include file "global.h" 
*
* 1. should define the structural type with basic type of info 
*    placed on the list named   ListInfo
*    // int  nKey - which will be used to compare items
*    // int* pTab - the dynamic table size of 2,
*
* 2. should define the preprocesor constant (LISTINFO)
*    as the basic type of info placed on the list  (defined as ListInfo)
*
* 3. should define the header of the comparision function

     int comp( const void*, const void* ); 
*    int (__cdecl* <COMPARISION_FUNCT_NAME>)( const void*, const void* ) // tak def jako parametr funkcji w module listy
                                                                        // gdy przekazujemu ja jako parametr fun 
*    which compares two items in the list
*    Function returns -1 if the first item is less then the second one
*                      0 if both items are equels
*                      1 if the first item is greater than the second one 
*      This function could be implment in the file with the main() function 
*
* 4. should define the header of the function to release memmory       
     void freemem( const void* );
*    void  (__cdecl* <FUNCTI_NAME>)( const void* )   // tak def jako parametr funkcji w module listy
                                                     // gdy przekazujemu ja jako parametr fun 

*      This function could be implment in the file with the main() function 
*
*---------------------------------------------------------------
*/

/*
* __cdecl to domyślna konwencja wywoływania dla programów C i C++. Przekazywanie parametrow zawsze przez stos,
* w kolejnosci od prawej do lewej, ktory jest czyszczony przez obiekt wywołujący!!. 
* Konwencja __cdecl wywoływania tworzy większe pliki wykonywalne 
* niż __stdcall, ponieważ wymaga dla każdego wywołania funkcji kodu oczyszczania stosu. 
* Modyfikator __cdecl jest specyficzny dla firmy Microsoft.

* __stdcall - Konwencja służy do wywoływania funkcji interfejsu API Win32. Przekazywanie parametrow przez stos, 
* w kolejnosci od prawej do lewej. Obiekt wywoływany czyści stos!!. 
* __stdcall Modyfikator jest specyficzny dla firmy Microsoft.
*/

#endif



















#ifndef _GLOBAL_H

#define _GLOBAL_H

typedef struct
{
  int nKey;
  int* pTab;

}UserType;

#define LISTINFO UserType

int Compare( const void*, const void* );
void FreeMem( const void* );


#endif