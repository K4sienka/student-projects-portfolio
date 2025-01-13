#include "FQueue.h"



bool FQueue::FQEmpty()      //mozna tez inlinem w .h
{
    return !(m_Head);			//sprawdzenie czy kolejka jest pusta
}


int FQueue::FQEnqueue (FQINFO* pInfo)
{
    FifoItem* item = new(nothrow) FifoItem(pInfo); //alokacja pamieci dla nowego obiektu klasy
    if (item)
    {
       ( FQEmpty() ? m_Head = item : m_Tail->m_pNext = item ); //jesli pusta tworzymy glowe, jesli nie to kolejny jej obiekt (rownoczesnie jej koniec)
        m_Tail = item;  //wskaznik na nowy koniec
    }
    else throw FifoException(FIFO_ALLOCATION_ERROR);
}


FQINFO* FQueue::FQDequeue()
{
    if (!FQEmpty())
    {
        FQINFO* pInfo = m_Head->m_pItem; //pobranie info o pierwszym elemencie
        FQDel();                          //usuniecie go
        return pInfo;                           //zwrocenie z niego wskaznika
    }
    else throw FifoException(FIFO_ALLOCATION_ERROR);
}


void FQueue::FQClear()
{
    while (!FQEmpty())      //dopoki nie jest pusta
        delete FQDequeue();   //czysci kolejke
}


void FQueue::FQPrint()
{
    FifoItem* item = m_Head;
    while (item)
    {
        cout << *(item->m_pItem) << endl;
        item = item->m_pNext;
    }
}

//

void FQueue::FQDel()
{
    if (!FQEmpty())
    {
        FifoItem* item = m_Head;    //1 elem
        m_Head = item->m_pNext;     //nastepny elem
        if (FQEmpty())
            m_Tail = NULL;      //usuwaj dopoki nie ostatni elem
        delete item;
    }
    else throw FifoException(FIFO_QUEUE_EMPTY);
}