// Algorytm Brona-Kerboscha
// Data   : 10.07.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <iomanip>

using namespace std;

// Definicja elementu listy s¹siedztwa

struct slistEl
{
  slistEl *next;                  // Nastêpny element listy
  int v;                          // Wierzcho³ek docelowy
};

// Definicja struktury zbioru

struct s_set
{
  int vmin,nmax;
  unsigned int *T;
};

// Zmienne globalne

int n,m;                          // Liczba wierzcho³ków i krawêdzi grafu
slistEl ** graf;                  // Tablica list s¹siedztwa
s_set SN;                         // Zbiór s¹siadów
int rcnt = 0;                     // Licznik wywo³añ rekurencyjnych

// Obs³uga zbiorów

// Procedura dodaje element x do zbioru A
//---------------------------------------
void s_add(s_set & A, int x)
{
  int b = x - A.vmin;             // Obliczamy numer bitu
  int i = b >> 5;                 // Obliczamy indeks
  A.T[i] |= 1 << (b & 31);        // Ustawiamy bit na 1
}

// Procedura usuwa element x ze zbioru
//------------------------------------
void s_remove(s_set & A, int x)
{
  int b = x - A.vmin;             // Obliczamy numer bitu
  int i = b >> 5;                 // Obliczamy indeks
  A.T[i] &= ~(1 << (b & 31));     // Ustawiamy bit na 0
}

// Procedura usuwa wszystkie elementy ze zbioru
//---------------------------------------------
void s_clear(s_set & A)
{
  for(int i = 0; i <= A.nmax; i++) A.T[i] = 0; // Zerujemy mapê bitow¹
}

// Procedura tworzy zbiór
//-----------------------
void s_create(s_set & A, int vmin, int vmax)
{
  A.vmin = vmin;                  // Wype³niamy strukturê danymi
  A.nmax = (vmax - vmin) >> 5;    // Indeks ostatniego elementu tablicy
  A.T = new unsigned int [A.nmax + 1];  // Tworzymy dynamicznie tablicê mapy bitowej
  s_clear(A);                     // Tworzymy zbiór pusty
}

// Procedura wyznacza czêœæ wspóln¹ zbiorów A i B
//-----------------------------------------------
void s_intersection(s_set & A, s_set & B, s_set & C)
{
  for(int i = 0; i <= A.nmax; i++) C.T[i] = A.T[i] & B.T[i];
}

// Procedura kopiuje zbiór A do zbioru B
//--------------------------------------
void s_copy(s_set & A, s_set & B)
{
  for(int i = 0; i <= A.nmax; i++) B.T[i] = A.T[i];
}

// Procedura ustawia zbiór pe³ny
//------------------------------
void s_full(s_set & A)
{
  for(int i = 0; i <= A.nmax; i++) A.T[i] = 0xffffffff;
}

// Funkcja sprawdza, czy zbiór A jest pusty
// true  - tak, jest pusty
// false - nie, nie jest pusty
//-----------------------------------------
bool s_empty(s_set A)
{
  unsigned int m = A.T[0];        // Pobieramy bity do m
  for(int i = 1; i <= A.nmax; i++) m |= A.T[i]; // Sumujemy logicznie bity
  return (m == 0);
}

// Funkcja bada, czy element x nale¿y do zbioru A
// true  - tak, nale¿y
// false - nie, nie nale¿y
//-----------------------------------------------
bool s_isin(s_set & A, int x)
{
  int b = x - A.vmin;             // Obliczamy numer bitu w mapie bitowej
  if(A.T[b >> 5] & (1 << (b & 31))) return true;
  return false;
}

// Procedura wyœwietla elementy zbioru A
//--------------------------------------
void s_print(s_set A)
{
  int nb;
  unsigned int m;

  for(int i = 0; i <= A.nmax; i++)
    for(nb = 0,m = A.T[i]; m; m >>= 1,nb++)
      if(m & 1) cout << (i << 5) + nb + A.vmin << " ";
}

// Procedura wyszukuje kliki maksymalne
//-------------------------------------
void BronKerbosch(s_set & SR, s_set & SP, s_set & SX)
{
  s_set RP,PP,XP;
  slistEl * p;
  int v;

  rcnt++;                         // Zwiêkszamy licznik wywo³añ rekurencyjnych

  if(s_empty(SP) && s_empty(SX))  // Jeœli zbiory SP i SX s¹ puste,
  {                               // to SR zawiera wierzcho³ki kliki maksymalnej
    cout << "MAXIMAL CLIQUE: ";
    s_print(SR);
    cout << endl;
  }
  else
  {
    s_create(RP,0,n-1);           // Tworzymy puste zbiory pomocnicze
    s_create(PP,0,n-1);
    s_create(XP,0,n-1);
    for(v = 0; v < n; v++)        // Przechodzimy przez kolejne wierzcho³ki grafu
      if(s_isin(SP,v))            // Jeœli wierzcho³ek v jest w zbiorze SP, to
      {                           // go przetwarzamy
        s_clear(SN);              // Najpierw zerujemy zbiór s¹siadów
        for(p = graf[v];p;p = p->next) // Przegl¹damy listê s¹siedztwa wierzcho³ka v
          s_add(SN,p->v);         // Ka¿dego s¹siada umieszczamy w SN
        s_copy(SR,RP);            // W RP tworzymy zbiór SR z dodanym wierzcho³kiem v
        s_add(RP,v);
        s_intersection(SP,SN,PP); // W PP tworzymy iloczyn SP i SN
        s_intersection(SX,SN,XP); // W XP tworzymy iloczyn SX i SN
        BronKerbosch(RP,PP,XP);   // Wywo³anie rekurencyjne
        s_remove(SP,v);           // Z SP usuwamy wierzcho³ek v
        s_add(SX,v);              // i dodajemy go do SX
      }
    delete [] RP.T;              // Usuwamy zbiory pomocnicze
    delete [] PP.T;
    delete [] XP.T;
  }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  s_set SR,SP,SX;
  int i,u,v;
  slistEl *p,*r;

  cin >> n >> m;                  // Odczytujemy liczbê wierzcho³ków i krawêdzi

  s_create(SR,0,n-1);             // Tworzymy puste zbiory
  s_create(SP,0,n-1);
  s_create(SX,0,n-1);
  s_create(SN,0,n-1);

  graf = new slistEl * [n];       // Tworzymy tablicê list s¹siedztwa

  for(i = 0; i < n; i++) graf[i] = NULL; // Zerujemy listy s¹siedztwa

  for(i = 0; i < m; i++)
  {
    cin >> u >> v;                // Wierzcho³ki krawêdzi
    p = new slistEl;              // Tworzymy element listy
    p->v = u;
    p->next = graf[v];            // Element do³¹czamy do listy s¹siadów v
    graf[v] = p;

    p = new slistEl;              // To samo dla krawêdzi w drug¹ stronê
    p->v = v;
    p->next = graf[u];            // Element do³¹czamy do listy s¹siadów u
    graf[u] = p;
  }

  s_full(SP);                     // W zbiorze SP ustawiamy wszystkie wierzcho³ki

  cout << endl;

  BronKerbosch(SR,SP,SX);         // Szukamy rekurencyjnie klik maksymalnych

  cout << endl << "RECURSIVE CALLS = " << rcnt << endl << endl;

  delete [] SR.T;                 // Usuwamy zbiory
  delete [] SP.T;
  delete [] SX.T;
  delete [] SN.T;

  for(v = 0; v < n; v++)          // Usuwamy tablicê list s¹siedztwa
  {
    p = graf[v];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] graf;

  return 0;
} 