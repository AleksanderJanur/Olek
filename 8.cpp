// Kody bezprzystankowe
// Data: 26.06.2013
// (C)2013 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <string>

using namespace std;

// Definicja wêz³a drzewa kodu bezprzystankowego
//----------------------------------------------
struct TNode
{
  TNode * left;
  TNode * right;
  char key;
};

// Tworzy z danych wejœciowych
// drzewo kodu bezprzystankowego
//------------------------------
void makeT(TNode * & root)
{
  int n,i,j;
  char s;
  string b;
  TNode * p;

  root = new TNode;             // Tworzymy wêze³ startowy
  root->left  = NULL;           // Wype³niamy pola
  root->right = NULL;

  cin >> n;                     // Odczytujemy liczbê definicji

  for(i = 0; i < n; i++)        // W pêtli tworzymy drzewo
  {
    cin >> s >> b;              // Czytamy znak i kod

    p = root;                   // Rozpoczynamy od korzenia

    for(j = 0; j < (int)b.length(); j++)  // Przetwarzamy kolejne bity kodu
      if(b[j] == '0')                // Czy bit = 0?
      {
        if(!p->left)                 // Czy istnieje lewy syn?
        {
          p->left = new TNode;       // Jeœli nie, to go tworzymy
          p->left->left  = NULL;
          p->left->right = NULL;
        }
        p = p->left;                 // Przechodzimy do lewego syna
      }
      else                           // To samo dla bit = 1
      {
        if(!p->right)                // Czy istnieje prawy syn?
        {
          p->right = new TNode;      // Jeœli nie, to go tworzymy
          p->right->left  = NULL;
          p->right->right = NULL;
        }
        p = p->right;          // Przechodzimy do prawego syna
      }

    p->key = s;                // Do liœcia wstawiamy znak

  }
}

// Dekoduje wiadomoœæ w kodzie bezprzystankowym
//---------------------------------------------
void decodeT(TNode * root)
{
  TNode * p;
  string b;
  int i;

  cin >> b;                   // Odczytujemy kod

  cout << endl;

  p = root;                   // Bie¿¹cy wêze³ ustawiamy na pocz¹tek drzewa

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

// Procedura DFS:postorder usuwaj¹ca drzewo
//-----------------------------------------
void DFSRelease(TNode * v)
{
  if(v)
  {
    DFSRelease(v->left);   // usuwamy lewe poddrzewo
    DFSRelease(v->right);  // usuwamy prawe poddrzewo
    delete v;              // usuwamy sam wêze³
  }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  TNode * root;            // Korzeñ drzewa

  makeT(root);             // Tworzymy drzewo kodu bezprzystankowego
  decodeT(root);           // Dekodujemy wiadomoœæ
  DFSRelease(root);        // Usuwamy drzewo z pamiêci

  return 0;
} 