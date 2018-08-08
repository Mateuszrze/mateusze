#include<bits/stdc++.h>
 
using namespace std;
typedef long long LL;

const int pot = 1<<20; // rozmiar tablicy na ktorej to robimy, numerowane od 0 do pot - 1
 
const LL inf = 1e9 + 7; // cos co jest > od kazdego elementu w tablicy
LL maxi[2 * pot + 7];
int ilemaxi[ 2 * pot + 7];
LL dru[ 2 * pot + 7];
LL suma[ 2 * pot  + 7];
LL propag[2 * pot + 7];
 
inline void update(int wierz)
{
      if(maxi[2 * wierz] == maxi[ 2 * wierz + 1])
      {
            maxi[wierz] = maxi[2 * wierz];
            ilemaxi[wierz] = ilemaxi[2 * wierz +  1] + ilemaxi[ 2 * wierz];
            dru[wierz] = max(dru[2 * wierz], dru[2 * wierz + 1]);
      }
      else
      {
            maxi[wierz] = max(maxi[ 2 * wierz], maxi[2 * wierz + 1]);
            if(maxi[wierz] == maxi[ 2 * wierz])
                  ilemaxi[wierz] = ilemaxi[2 * wierz];
            else
                  ilemaxi[wierz] = ilemaxi[2 * wierz + 1];
            dru[wierz] = max(max(min(maxi[ 2 * wierz], maxi[2 * wierz + 1]), dru[2 * wierz]), dru[ 2 * wierz + 1 ]);
      }
      suma[wierz] = suma[ 2 * wierz] + suma[ 2  * wierz + 1];
}
 
void propagate(int cur)
{
      LL val = propag[cur];
      propag[cur] = inf;
 
      if(maxi[2 * cur] > val)
      {
            propag[2 * cur] = val;
            suma[2 * cur] -= maxi[2 * cur] * (LL) ilemaxi[2 * cur];
            maxi[2 * cur] = val;
            suma[2 * cur] += maxi[ 2 * cur] * (LL) ilemaxi[2 * cur];
      }
 
      if(maxi[2 * cur + 1] > val)
      {
            propag[2 * cur + 1] = val;
            suma[2 * cur + 1] -= maxi[2 * cur + 1] * (LL) ilemaxi[2 * cur + 1];
            maxi[2 * cur + 1] = val;
            suma[2 * cur + 1] += maxi[ 2 * cur + 1] * (LL) ilemaxi[2 * cur + 1];
      }
}
 
void ustaw(int l, int p, LL val, int cur = 1, int lewo = 0, int prawo = pot - 1) // na przedziale l, p wykonaj operacje tab[i] = min(tab[i], val)
{
      if(p < lewo || l > prawo)
            return ;
      if(l <= lewo && prawo <= p)
      {
            if(val > maxi[cur])
                  return ;
            if(dru[cur] < val)
            {
                  suma[cur] -= maxi[cur] * (LL) ilemaxi[cur];
                  maxi[cur] = val;
                  suma[cur] += maxi[cur] * (LL) ilemaxi[cur];
                  propag[cur] = val;
                  return ;
            }
      }
      propagate(cur);
      int sr = (lewo + prawo) / 2;
      ustaw(l, p, val, 2 * cur, lewo, sr);
      ustaw(l, p, val, 2 * cur + 1, sr + 1, prawo);
      update(cur);
}
 
LL ask(int l, int p, int wierz = 1, int lewo = 0, int prawo = pot - 1)
{
      if(p < lewo || l > prawo)
            return 0LL;
      if(l <= lewo && prawo <= p)
            return suma[wierz];
      propagate(wierz);
      int sr = (lewo + prawo) / 2;
      LL res = ask(l, p, 2 * wierz, lewo, sr) + ask(l, p , 2 * wierz + 1, sr + 1, prawo);
      update(wierz);
      return res;
}

void preust(int x, LL val) // tutaj wstawiasz wartosc poczatkowa (przed odpaleniem funcji start
{
	suma[x + pot] = maxi[x + pot] = val;
	dru[x + pot] = 0;
}

void start()
{
	for(int i = 0 ;i < 2 * pot;i++)
	{
		propag[i] = inf;
		ilemaxi[i] = 1;
	}
	for(int i = pot - 1 ;i > 0;i--)
		update(i);
}

int main()
{
	preust(1, 10);
	start();
	ustaw(1, 10, 10);
	ask(1, 10); 
}
 
 
