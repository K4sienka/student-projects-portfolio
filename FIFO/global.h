#pragma once
#include <iostream>
using namespace std; 

#define FQINFO FQInfo //zdef stala preprocesora FQINFO jako struktura FQInfo

struct FQInfo //w global.h  zdef klase (strukt) FQInfo z polami 
{
public:
	int nKey;
	int* p;		//dwuelementowa

	FQInfo(int key);
	virtual ~FQInfo(); 

	friend ostream& operator << (ostream& out, const FQINFO& q);
};

inline FQInfo::FQInfo(int key)
{
	nKey = key;		//przechowywanie info o kluczu
	p = new int[2]; //new int przydziela pamiec do p
	p[0] = key;		//key to pierwszy element
}

inline FQInfo::~FQInfo()  //zwolnienie pamieci
{
	delete[] p;
}

inline ostream& operator << (ostream& out, const FQINFO& q)
{
	out << "Klucz to " << q.nKey << "\n p[0] to " << q.p[0] <<endl;
	return out;
}