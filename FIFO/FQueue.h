#pragma once
#include "global.h"
#include <iostream>
using namespace std;

//Dodac do tego samego pliku naglowkowego obsluge wyjatkow
#define FIFO_ALLOCATION_ERROR	0x01
#define FIFO_QUEUE_EMPTY		0x04
#define OTHER_ERROR				0x10


class FifoException		//do obslugi wyjatkow
{
public:

	FifoException(int errCode = OTHER_ERROR);		//konstruktor
	const char* getReason();						//metoda getReason();  implementacja inline

private:
	int m_error;
};


inline FifoException::FifoException (int errCode /*= OTHER_ERROR*/) //konstruktor (inline) na bazie kodu bledu
{
	m_error = errCode;
}


inline const char* FifoException::getReason()	//metode inline zwrajaca(switch ()) odpowiedni string(const char*) opisujacy rodzaj bledu
{
	switch (m_error)
		{
			case FIFO_ALLOCATION_ERROR:	return "ALLOCATION ERROR";
			case FIFO_QUEUE_EMPTY:		return "QUEUE IS EMPTY";
			default:					return "ERROR!";
		}
}


/*----------------------------*/
class FQueue;

class FifoItem	//zdef klase: element kolejki FifoItem (nie zagniezdzona) pomocnicza dla klasy Fifo,
{
private:
	friend class FQueue;	//tylko w metodach klasy FQueue mozna wykreowac obiekt FifoItem 

	FQINFO* m_pItem;		//wsk m_pItem (wsk na FQINFO)
	FifoItem* m_pNext;		//wsk m_pNext (wsk na nastepny w kolejce)


	FifoItem(FQINFO* pInfo = NULL);	//konstr z parametrem domyslnym (NULL) - wsk na FQINFO (uzywamy stalej preprocesora WSZEDZIE)
	virtual ~FifoItem();
	FifoItem();
};


inline FifoItem::FifoItem() //konstruktor bezparametrowy do tworzenia obiektow klasy 
{
	m_pItem = NULL;
	m_pNext = NULL;
}

inline FifoItem::FifoItem(FQINFO* pInfo /*=NULL*/)
{
	m_pItem = pInfo;			//wskaznik jako argument pInfo
	m_pNext = NULL;			//poczatkowo nie wskazuje na konkretny obiekt
}

inline FifoItem::~FifoItem() { } //nieuzywany destruktor


/*----------------------------*/


class FQueue	//realizowany jako lista prosta (z glowa) z dwoma wskaznikami(m_pHead, m_pTail)
{
public:
	FQueue();				//konstruktor bez param
	virtual ~FQueue();		//wirt destr

	bool FQEmpty();					//czy pusta
	int FQEnqueue(FQINFO* pInfo);	//dodawanie
	FQINFO* FQDequeue();			//usuwanie i zwracanie
	void FQClear();					//czyszczenie pamieci

	void FQPrint();					//drukowanie

private:
	void FQDel();					//usuwanie elementu

//dwie glowy 
	FifoItem* m_Head;
	FifoItem* m_Tail;
};


inline FQueue::FQueue()
{								//kolejka na poczatku pusta
	m_Head = NULL;
	m_Tail = NULL;
}

inline FQueue::~FQueue()
{
	FQClear();				//czysci kolejke i pamiec
	delete m_Head;			//dodatkowe usuniecie glowy
}


