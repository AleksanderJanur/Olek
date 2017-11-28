// Problem komiwoja¿era
// Data: 22.03.2014
// (C)2014 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>

using namespace std;

const int MAXINT = 2147483647;

// Zmienne globalne

int n,m,v0,d,dh,sptr,shptr;
bool **A;                         // Macierz s¹siedztwa
int **W;                          // Macierz wag krawêdzi
int *S,*Sh;                       // Stosy w tablicy
bool *visited;                    // Tablica odwiedzin

// Rekurencyjna procedura poszukiwania cyklu Hamiltona
// o najmniejszej sumie wag krawêdzi
// v - wierzcho³ek bie¿¹cy
//----------------------------------------------------
void TSP(int v)
{
  int u;

  Sh[shptr++] = v;                // zapamiêtujemy na stosie bie¿¹cy wierzcho³ek

  if(shptr < n)                   // jeœli brak œcie¿ki Hamiltona, to jej szukamy
  {
    visited[v] = true;            // Oznaczamy bie¿¹cy wierzcho³ek jako odwiedzony
    for(u = 0; u < n; u++)        // Przegl¹damy s¹siadów wierzcho³ka v
      if(A[v][u] && !visited[u])  // Szukamy nieodwiedzonego jeszcze s¹siada
      {
        dh += W[v][u];            // Dodajemy wagê krawêdzi v-u do sumy
        TSP(u);                   // Rekurencyjnie wywo³ujemy szukanie cyklu Hamiltona
        dh -= W[v][u];            // Usuwamy wagê krawêdzi z sumy
      }
    visited[v] = false;           // Zwalniamy bie¿¹cy wierzcho³ek
  }
  else if(A[v0][v])               // Jeœli znaleziona œcie¿ka jest cyklem Hamiltona
  {
    dh += W[v][v0];               // to sprawdzamy, czy ma najmniejsz¹ sumê wag
    if(dh < d)                    // Jeœli tak,
    {
      d = dh;                     // To zapamiêtujemy tê sumê
      for(u = 0; u < shptr; u++)  // oraz kopiujemy stos Sh do S
        S[u] = Sh[u];
      sptr = shptr;
    }
    dh -= W[v][v0];               // Usuwamy wagê krawêdzi v-v0 z sumy
  }
  shptr--;                        // Usuwamy bie¿¹cy wierzcho³ek ze œcie¿ki
}

//**********************
//*** Program g³ówny ***
//**********************

int main()
{
  int i,j,x,y,z;

  cin >> n >> m;                  // Czytamy liczbê wierzcho³ków i krawêdzi

  // Tworzymy struktury dynamiczne i inicjujemy je

  S       = new int [n];
  Sh      = new int [n];
  visited = new bool [n];
  A       = new bool * [n];
  W       = new int * [n];
  for(i = 0; i < n; i++)
  {
    A[i] = new bool [n];
    W[i] = new int [n];
    for(j = 0; j < n; j++)
    {
      A[i][j] = false;
      W[i][j] = 0;
    }
    visited[i] = false;
  }
  sptr = shptr = 0;

  // Odczytujemy dane wejœciowe

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> z;
    A[x][y] = A[y][x] = true;     // KrawêdŸ x-y
    W[x][y] = W[y][x] = z;        // Waga krawêdzi x-y
  }

  cout << endl;

  // Rozpoczynamy algorytm

  d  = MAXINT;
  dh = v0 = 0;
  TSP(v0);
  if(sptr)
  {
    for(i = 0; i < sptr; i++) cout << S[i] << " ";
    cout << v0 << endl;
    cout << "d = " << d << endl;
  }
  else cout << "NO HAMILTONIAN CYCLE" << endl;

  cout << endl;

  // Usuwamy tablice dynamiczne

  delete [] S;
  delete [] Sh;
  delete [] visited;

  for(i = 0; i < n; i++)
  {
    delete [] A[i];
    delete [] W[i];
  }

  delete [] A;
  delete [] W;

  return 0;
} 