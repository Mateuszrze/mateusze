#include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second
#define pb push_back

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector < int > VI;
typedef double D;

const int MN = 200005, inf = 1000000005, mod = 1000000007;
const LL INF = 1000000000000000005LL;

int czas;
int pod[MN], naj[MN], used[MN], blocked[MN];
VI V, G[MN];


void licz(int x)
{
	//coś liczymy
	//gdy odpalamy dfsa, to zwiększamy czas!
	//wchodzimy tylko gdy used[v] != czas && !blocked[v]
}

void dfs(int x)
{
	used[x] = czas;
	pod[x] = 1, naj[x] = 0;
	V.pb(x);
	for(auto v : G[x])
		if(used[v] != czas && !blocked[v])
		{
			dfs(v);
			pod[x] += pod[v];
			naj[x] = max(naj[x], pod[v]);
		}
}

int centro(int x)
{
	++czas;
	V.clear();
	dfs(x);
	int siz = pod[x], hf = pod[x] >> 1;
	for(auto v : V)
		if(max(naj[v], siz - pod[v]) <= hf)
			return v;
	assert(0);
}

void decomp(int x)
{
	x = centro(x);
	blocked[x] = 1;
	licz(x);
	for(auto v : G[x])
		if(!blocked[v])
			decomp(v);
}

int main()	
{
	int n;
	V.reserve(n + 5);
	decomp(1);
}
