// Rozk³ad LU algorytmem Doolitle'a
// Data: 21.03.2010
// (C)2012 mgr Jerzy Wa³aszek
//-----------------------------

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double eps = 1e-12;

// Funkcja realizuje algorytm Doolitle'a rozk³adu LU
//--------------------------------------------------
bool Doolitle(int n, double ** A)
{
  int i,j,k;
  double s;
  
  for(j = 0; j < n; j++)
  {
    if(fabs(A[j][j]) < eps) return false;
    for(i = 0; i <= j; i++)
    {
      s = 0;
      for(k = 0; k < i; k++) s +=  A[i][k] * A[k][j];
      A[i][j] -= s;
    }
    for(i = j + 1; i < n; i++)
    {
      s = 0;
      for(k = 0; k < j; k++) s += A[i][k] * A[k][j];
      A[i][j] = (A[i][j] - s) / A[j][j];
    }
  }
  return true;
}

// Program g³ówny

int main()
{
  double **A;
  int n,i,j;
  
  cout << setprecision(3) << fixed;
  
// odczytujemy stopieñ macierzy A

  cin >> n;

  // tworzymy macierz A o odpowiednich rozmiarach

  A = new double * [n];
  for(i = 0; i < n; i++) A[i] = new double [n];

  // odczytujemy dane dla macierzy A

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) cin >> A[i][j];

  // wyznaczamy rozk³ad LU macierzy A

  if(Doolitle(n,A))
    for(i = 0; i < n; i++)
    {
      for(j = 0; j < n; j++)
        cout << setw(8) << A[i][j] << " ";
      cout << endl;
    }
  else
    cout << "DZIELNIK ZERO\n";

  // usuwamy macierz z pamiêci

  for(i = 0; i < n; i++) delete [] A[i];
  delete [] A;
  return 0;
} 