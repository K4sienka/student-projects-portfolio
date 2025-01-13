#include <iostream>
using namespace std;

#include "FQueue.h"

int main()
{
    FQueue q;       //tworzenie kolejki

    FQINFO* x = new FQINFO(14);
    FQINFO* y = new FQINFO(24);
    FQINFO* z = new FQINFO(3);      //3 elementy

    q.FQEnqueue(x);     //dodajemy je do kolejki
    q.FQEnqueue(y);
    q.FQEnqueue(z);
    cout << "Wszystkie elementy" << endl;
    q.FQPrint();           //drukujemy
    FQINFO* item = q.FQDequeue(); 
    cout << "Usuniety element to\n" << * (item) << endl; //usuniety element
    delete item;
    cout << "Reszta elementow to" << endl;
    q.FQPrint();
    q.FQClear();
    cout << "\nSprawdzenie czy wyczyscilo kolejke" << endl;
    
    return 0;
}
