// Wyszukiwanie w drzewie BST
// Data: 24.04.2013 /Zmiana Marcina!!!/
// (C)2013 mgr Jerzy Wa³aszek
//------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Typ wêz³ów drzewa BST

struct BSTNode
{
  BSTNode * left;
  BSTNode * right;
  int key;
};

// Funkcja wczytuje drzewo BST ze standardowego
// wejœcia i zwraca wskazanie korzenia.
//-----------------------------------------------
BSTNode * readBST()
{
  BSTNode ** vp;    // Tablica wskazañ wêz³ów
  int key,l,r,i,n;

  cin >> n;                 // Odczytujemy liczbê wêz³ów drzewa

  vp = new BSTNode * [n];   // Tworzymy dynamiczn¹ tablicê wskazañ wêz³ów

  // Tablicê dynamiczn¹ wype³niamy wskazaniami wêz³ów,
  // które równie¿ tworzymy dynamicznie

  for(i = 0; i < n; i++) vp[i] = new BSTNode;

  // Teraz wczytujemy definicjê drzewa i tworzymy jego strukturê
  // w pamiêci wype³niaj¹c odpowiednie pola wêz³ów.

  for(i = 0; i < n; i++)
  {
    cin >> key >> l >> r;   // Czytamy klucz, numer lewego i prawego syna

    vp[i]->key = key;       // Ustawiamy klucz

    vp[i]->left  = l ? vp[l]: NULL;  // Ustawiamy lewego syna

    vp[i]->right = r ? vp[r]: NULL;  // Ustawiamy prawego syna

  }

  BSTNode * p = vp[0];      // Zapamiêtujemy korzeñ

  delete [] vp;             // Usuwamy tablicê dynamiczn¹

  return p;
}

// Funkcja szuka w drzewie BST wêz³a o zadanym kluczu.
// Jeœli go znajdzie, zwraca jego wskazanie. Je¿eli nie,
// to zwraca wskazanie puste.
// Parametrami s¹:
// p - wskazanie korzenia drzewa BST
// k - klucz poszukiwanego wêz³a
//----------------------------------------------------
BSTNode * findBST(BSTNode * p, int k)
{
  while(p && p->key != k)
    p = (k < p->key) ? p->left: p->right;

  return p;
}

// Funkcja zwraca wskazanie wêz³a o najmniejszym kluczu.
// Parametrem jest wskazanie korzenia drzewa BST.
//------------------------------------------------------
BSTNode * minBST(BSTNode * p)
{
  if(p) while(p->left) p = p->left;

  return p;
}

// Funkcja zwraca wskazanie wêz³a o najwiêkszym kluczu.
// Parametrem jest wskazanie korzenia drzewa BST.
//------------------------------------------------------
BSTNode * maxBST(BSTNode * p)
{
  if(p) while(p->right) p = p->right;

  return p;
}

// Procedura DFS:postorder usuwaj¹ca drzewo
//-----------------------------------------
void DFSRelease(BSTNode * v)
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
  BSTNode * root, * p;
  int k, mink, maxk;

  root = readBST();     // Odczytujemy drzewo BST

  if(root)
  {
    mink = minBST(root)->key; // Odczytujemy klucz minimalny
    maxk = maxBST(root)->key; // Odczytujemy klucz maksymalny

    // Przechodzimy przez kolejne wartoœci kluczy

    for(k = mink; k <= maxk; k++)
    {
      p = findBST(root,k);    // szukamy wêz³a o kluczu k

      cout << "KEY = " << setw(3) <<  k << " : ";

      if(p)
      {
        if (!p->left && !p->right) cout << "LEAF";
        else                       cout << "INNER NODE";
      }
      else cout << "NONE";

      cout << endl;
    }
  }
  else cout << "BST is empty!!!" << endl;

  DFSRelease(root);    // usuwamy drzewo z pamiêci

  return 0;
} 