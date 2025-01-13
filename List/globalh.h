#pragma once //zabezpieczenie przed wielokrotnym includowaniem

typedef struct ListElements
{
  int nKey;       //do porownywania itemow
  int* pTab;      //tablica o rozmiarze 2

}Informations;

#define LISTINFO Informations    //stala preprocesora

int comp( const void*, const void* );   //funkcja do porownywania

void freemem( const void* );            //zwalnianie pamieci
