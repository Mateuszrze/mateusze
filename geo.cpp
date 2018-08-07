//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
//~ #pragma GCC optimize("O3")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) ((int)(x).size())
#define ALL(x) x.begin(),x.end()
#define all(x) x.begin(),x.end()
#define fi first
#define se second
#define _upgrade ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<PII> VPII;
typedef vector<PLL> VPLL;
typedef vector<LL> VLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<char> VC;
typedef long double LD;
typedef pair<LD,LD> PLD;
typedef vector<LD> VLD;
typedef vector<PLD> VPLD;

template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<" = "<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<" = "<<h<<", "; _dbg(sdbg+1, a...);
}

#ifdef LOCAL
#define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...)
#define cerr if(0)cout
#endif

const int maxn = (1e6)+7;
const int maxk = 20;
const int inf = (1e9)+7;
const LL LLinf = (1e18)+7;
const LD eps = 1e-9;
const LL mod = 1e9+7;

// ***************************** CODE ***************************** //

struct point
{
	LL x, y;
	
	point(LL a, LL b) // konstruktor {a, b} dziala
	{
		x = a;
		y = b;
	}
	
	point operator-(const point a)
	{
		return point(x - a.x, y - a.y);
	}
	
	void operator-=(const point & b)
	{
		x -= b.x;
		y -= b.y;
	}
	
	bool gora() // (0, 0) jest w gorze
	{
		if(y > 0 || (y == 0 && x >= 0))
			return 1;
		return 0;
	}
	
};

LL wyz(point a, point b, point c) // wzraca wyznacznik 
{
	b -= a;
	c -= a;
	return b.x * c.y - b.y * c.x;
}

int wyzznak(point a, point b, point c) // zwraca znak wyznacznika
{
	LL res = wyz(a, b, c);
	if(res > 0)
		return 1;
	if(res == 0)
		return 0;
	return -1;
}

LL skalar(point a, point b) // iloczn skalarny
{
	return a.x * b.x + a.y * b.y;
}

bool angcomp(point & a, point & b) // komparator do sortowania katowego
{
	if(a.gora() != b.gora())
		return b.gora() < a.gora();
	return wyzznak(point(0, 0), a, b) == 1; 
}

struct line
{
	LD a, b, c;
	
	line(LD A, LD B, LD C)
	{
		a = A;
		b = B;
		c = C;
	}
	
	line(point A, point B)
	{
		a = A.y - B.y;
		b = B.x - A.x;
		c = A.y * (A.x - B.x) + (B.y - A.y) * A.x;
	}

};

// punktprzeciecia dwoch prostych
point inter(line a, line b)
{
	if((a.a * b.b - a.b * b.a) < eps)
		return {0, 0}; // te proste sie nie przecinaja
	return {(b.b * a.c - a.b * b.c ) / (b.a * a.b - a.a - b.b), (b.a * a.c - a.a * b.c) / (a.a * b.b - b.a * a.b)};
}

int main()
{
	_upgrade
	
	return 0;
}
