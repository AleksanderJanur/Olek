// Problem komiwoja�era
// Data: 22.03.2014
// (C)2014 mgr Jerzy Wa�aszek
//---------------------------

#include <iostream>

using namespace std;

const int MAXINT = 2147483647;

// Zmienne globalne

int n,m,v0,d,dh,sptr,shptr;
bool **A;                         // Macierz s�siedztwa
int **W;                          // Macierz wag kraw�dzi
int *S,*Sh;                       // Stosy w tablicy
bool *visited;                    // Tablica odwiedzin

// Rekurencyjna procedura poszukiwania cyklu Hamiltona
// o najmniejszej sumie wag kraw�dzi
// v - wierzcho�ek bie��cy
//----------------------------------------------------
void TSP(int v)
{
  int u;

  Sh[shptr++] = v;                // zapami�tujemy na stosie bie��cy wierzcho�ek

  if(shptr < n)                   // je�li brak �cie�ki Hamiltona, to jej szukamy
  {
    visited[v] = true;            // Oznaczamy bie��cy wierzcho�ek jako odwiedzony
    for(u = 0; u < n; u++)        // Przegl�damy s�siad�w wierzcho�ka v
      if(A[v][u] && !visited[u])  // Szukamy nieodwiedzonego jeszcze s�siada
      {
        dh += W[v][u];            // Dodajemy wag� kraw�dzi v-u do sumy
        TSP(u);                   // Rekurencyjnie wywo�ujemy szukanie cyklu Hamiltona
        dh -= W[v][u];            // Usuwamy wag� kraw�dzi z sumy
      }
    visited[v] = false;           // Zwalniamy bie��cy wierzcho�ek
  }
  else if(A[v0][v])               // Je�li znaleziona �cie�ka jest cyklem Hamiltona
  {
    dh += W[v][v0];               // to sprawdzamy, czy ma najmniejsz� sum� wag
    if(dh < d)                    // Je�li tak,
    {
      d = dh;                     // To zapami�tujemy t� sum�
      for(u = 0; u < shptr; u++)  // oraz kopiujemy stos Sh do S
        S[u] = Sh[u];
      sptr = shptr;
    }
    dh -= W[v][v0];               // Usuwamy wag� kraw�dzi v-v0 z sumy
  }
  shptr--;                        // Usuwamy bie��cy wierzcho�ek ze �cie�ki
}

//**********************
//*** Program g��wny ***
//**********************

int main()
{
  int i,j,x,y,z;

  cin >> n >> m;                  // Czytamy liczb� wierzcho�k�w i kraw�dzi

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

  // Odczytujemy dane wej�ciowe

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> z;
    A[x][y] = A[y][x] = true;     // Kraw�d� x-y
    W[x][y] = W[y][x] = z;        // Waga kraw�dzi x-y
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