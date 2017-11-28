// Haszowanie z porcjowaniem
// Data: 16.06.2013
// (C)2013 mgr Jerzy Wa³aszek
//---------------------------

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definicja elementu listy
//-------------------------
struct slistEl
{
  slistEl * next;
  string data;
};

// Funkcja haszuj¹ca
//------------------
unsigned int hf(string s)
{
  unsigned int h,i;

  h = 0;
  for(i = 0; i < s.length(); i++)
    h = 31 * h + s[i] - 65;
  return h % 10;
}

//**********************
//*** PROGRAM G£ÓWNY ***
//**********************
int main()
{
  slistEl * T[10], * p, * r;
  unsigned int i,j,h,c;
  string s;
  bool t;

  srand(time(NULL));

  // Zerujemy tablicê haszowan¹
  for(i = 0; i < 10; i++) T[i] = NULL;

  // Tablicê wype³niamy ³añcuchami
  for(i = 0; i < 35; i++)
  {
    // Generujemy losowy ³añcuch z 4 znaków A-Z
    s = "";
    for(j = 0; j < 4; j++) s += 65 + (rand() % 26);

    // £añcuch umieszczamy na odpowiedniej liœcie
    h = hf(s);
    p = T[h];
    t = true;

    if(p)
      while(true)
      {
        if(p->data == s)
        {
          t = false;
          break;
        }
        if(!p->next) break;
        p = p->next;
      }

    if(t)
    {
      r = new slistEl;
      r->data = s;
      r->next = NULL;
      if(!p) T[h] = r;
      else p->next = r;
    }
  }

  // Wypisujemy tablicê
  for(i = 0; i < 10; i++)
  {
    cout << "T[" << i << "] = ";
    p = T[i];
    while(p)
    {
      cout << p->data << " ";
      p = p->next;
    }
    cout << endl;
  }

  cout << endl;

  // Generujemy wszystkie ³añcuchy 4-ro znakowe i szukamy ich w tablicy

  s = "AAAA";

  do
  {
    h = hf(s);
    c = 0;
    p = T[h];
    while(p && (p->data != s))
    {
      c++;
      p = p->next;
    }

    if(p) cout << s << " hf = " << h << " c = " << c << endl;

    for(i = 4; i > 0; i--)
    {
      s[i - 1] = s[i - 1] + 1;
      if(s[i - 1] <= 'Z') break;
      s[i - 1] = 'A';
    }
  } while(s != "AAAA");

  // Usuwamy listy z pamiêci

  for(i = 0; i < 10; i++)
    while((p = T[i]))
    {
      T[i] = p->next;
      p->data = "";
      delete p;
    }

  cout << endl;

  return 0;
} 