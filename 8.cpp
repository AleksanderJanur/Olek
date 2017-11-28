// Kody bezprzystankowe
// Data: 26.06.2013
// (C)2013 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream>
#include <string>

using namespace std;

// Definicja w�z�a drzewa kodu bezprzystankowego
//----------------------------------------------
struct TNode
{
  TNode * left;
  TNode * right;
  char key;
};

// Tworzy z danych wej�ciowych
// drzewo kodu bezprzystankowego
//------------------------------
void makeT(TNode * & root)
{
  int n,i,j;
  char s;
  string b;
  TNode * p;

  root = new TNode;             // Tworzymy w�ze� startowy
  root->left  = NULL;           // Wype�niamy pola
  root->right = NULL;

  cin >> n;                     // Odczytujemy liczb� definicji

  for(i = 0; i < n; i++)        // W p�tli tworzymy drzewo
  {
    cin >> s >> b;              // Czytamy znak i kod

    p = root;                   // Rozpoczynamy od korzenia

    for(j = 0; j < (int)b.length(); j++)  // Przetwarzamy kolejne bity kodu
      if(b[j] == '0')                // Czy bit = 0?
      {
        if(!p->left)                 // Czy istnieje lewy syn?
        {
          p->left = new TNode;       // Je�li nie, to go tworzymy
          p->left->left  = NULL;
          p->left->right = NULL;
        }
        p = p->left;                 // Przechodzimy do lewego syna
      }
      else                           // To samo dla bit = 1
      {
        if(!p->right)                // Czy istnieje prawy syn?
        {
          p->right = new TNode;      // Je�li nie, to go tworzymy
          p->right->left  = NULL;
          p->right->right = NULL;
        }
        p = p->right;          // Przechodzimy do prawego syna
      }

    p->key = s;                // Do li�cia wstawiamy znak

  }
}

// Dekoduje wiadomo�� w kodzie bezprzystankowym
//---------------------------------------------
void decodeT(TNode * root)
{
  TNode * p;
  string b;
  int i;

  cin >> b;                   // Odczytujemy kod

  cout << endl;

  p = root;                   // Bie��cy w�ze� ustawiamy na pocz�tek drzewa

  for(i = 0; i < (int)b.length(); i++)   // Przetwarzamy kolejne bity kodu
  {
    if(b[i] == '0') p = p->left;
    else            p = p->right;
    if(!p->left)
    {
      cout << p->key;
      p = root;
    }
  }

  cout << endl;

}

// Procedura DFS:postorder usuwaj�ca drzewo
//-----------------------------------------
void DFSRelease(TNode * v)
{
  if(v)
  {
    DFSRelease(v->left);   // usuwamy lewe poddrzewo
    DFSRelease(v->right);  // usuwamy prawe poddrzewo
    delete v;              // usuwamy sam w�ze�
  }
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  TNode * root;            // Korze� drzewa

  makeT(root);             // Tworzymy drzewo kodu bezprzystankowego
  decodeT(root);           // Dekodujemy wiadomo��
  DFSRelease(root);        // Usuwamy drzewo z pami�ci

  return 0;
} 