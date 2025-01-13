#include "Sort.h"

void quicksort( int* pTab, int a, int b );
void update ( int* pTab, int p, int k );

void BubblesSort( int* pTab, int nSize )     //wskaüniki
{
  for (int i = 0; i < nSize - 1; i++)
  {
    for (int j = nSize - 1; j > i; j--)
      if (pTab[j] < pTab[j - 1])
      {
        int x = pTab[j];
        pTab[j] = pTab[j - 1];
        pTab[j - 1] = x;
      }
  }
}

void SimpleSort( int* pTab, int nSize )
{
  for (int i = 1; i < nSize; i++)
  {
    int j = i - 1;
    int x = pTab[i];
    while (j >= 0 && pTab[j] > x)
    {
      pTab[j + 1] = pTab[j--];
      
    }
    pTab[j + 1] = x;
  }
}

void SimpleSelectionSort( int* pTab, int nSize )
{
  for (int i = 0; i < nSize-1; i++)
  {
    int x = pTab[i];
    int ix = i;
    for (int j = i + 1; j < nSize; j++)
      if (pTab[j] < x)
      {
        x = pTab[j];
        ix = j;
      }
    pTab[ix] = pTab[i];
    pTab[i] = x;
  }
}

void MixedSort( int* pTab, int nSize )
{
  int a = nSize;
  int b = 1;
  int c = nSize - 1;
  do {
    for (int j = c; j >= b; j--) 
    {
      if (pTab[j - 1] > pTab[j]) 
      {
        int w = pTab[j - 1];
        pTab[j - 1] = pTab[j];
        pTab[j] = w;
        a = j;
      }
    }
    
    b = a + 1;
    
    for (int j = b; j <= c; j++) 
    {
      if (pTab[j - 1] > pTab[j]) 
      {
        int w = pTab[j - 1];
        pTab[j - 1] = pTab[j];
        pTab[j] = w;
        a = j;
      }
    }
    c = a - 1;
  } while (b <= c);
}

void HalfInsertionSort( int* pTab, int nSize )
{
  for (int i = 1; i < nSize; i++) 
  {
    int t = pTab[i];
    int d = i - 1;
    int e = 0;
    while (e <= d) 
    {
      int f = (e + d) / 2;
      if (t < pTab[f]) d = f - 1;
      else e = f + 1;
    }

    for (int g = i - 1; g >= e; g--) 
    {
      pTab[g + 1] = pTab[g];
    }
    pTab[e] = t;
  }
}

void HeapSort ( int* pTab, int nSize )  //wywoluje update(), bez rekurencji 
{
  int k = nSize - 1;
  for( int p = nSize/ 2; p >= 0; p-- )
  {
    update( pTab, p, k );
  }
  for( ; k>0 ; k-- )
  {
    int x = pTab[0];
    pTab[0] = pTab[k];
    pTab[k] = x;
    update( pTab, 0, k-1 );
  }
}


void QuickSort( int* pTab, int nSize )
{
  quicksort( pTab, 0, nSize - 1 );    //quicksort( 3 parametry);
}

void quicksort( int* pTab, int a, int b )
{
  int i = a;
  int j = b;
  int w = pTab[(a + b) / 2];

  do              //repeat Pascal
  {
    while (pTab[i] < w) i++;
    while (w < pTab[j]) j--;
    if (i <= j)
    {
      int t = pTab[i];
      pTab[i] = pTab[j];
      pTab[j] = t;
      i++;
      j--;
    }
  } while (i <= j);
   if (i < b) quicksort( pTab, i, b );
   if (j > a) quicksort( pTab, a, j );
} 


void update ( int* pTab, int p, int k )
{
  if (p >= k) return;
  int i = p;
  int j = 2 * i + 1;
  int x = pTab[i];
  while (j <= k)
  {
    if (j < k)
    {
      if (pTab[j] < pTab[j + 1])
        j++;
    }
    if (x >= pTab[j]) break;
    pTab[i] = pTab[j];
    i = j;
    j = 2 * i + 1;
  }
  pTab[i] = x;
}

