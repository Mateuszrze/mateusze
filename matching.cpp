#include <bits/stdc++.h>

#define mp make_pair
#define fi first
#define se second
#define pb push_back

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector < int > VI;

const int MN = 20005;

struct matching
{
	VI G[MN], Pan;
	queue < int > Q;
	int skoj[MN], odw[MN], odl[MN];
	void addEdge(int a, int b)
	{
		G[a].pb(b);
		G[b].pb(a);
		Pan.pb(a);
	}
	void czysc()
	{
		while(!Q.empty())
			Q.pop();
		for(int i = 0; i < MN; ++i)
		{
			G[i].clear();
			skoj[i] = odw[i] = odl[i] = 0;
		}
	}
	void skojarz(int a, int b)
	{
		skoj[a] = b;
		skoj[b] = a;
	}
	int dfs(int x)
	{
		odw[x] = 1;
		for(auto v : G[x])
		{
			if(!skoj[v])
			{
				skojarz(x, v);
				return 1;
			}
			else if(!odw[skoj[v]] && odl[skoj[v]] == odl[x] + 1)
			{
				int duck = dfs(skoj[v]);
				if(duck)
				{
					skojarz(x, v);
					return 1;
				}
				
			}
		}
		return 0;
	}
	void match()
	{
		int lep = 1;
		while(lep)
		{
			lep = 0;
			for(auto v : Pan)
			{
				if(!skoj[v])
				{
					Q.push(v);
					odl[v] = 0;
				}
				else
				{
					odl[v] = -1;
				}
			}
		while(!Q.empty())
		{
			int cur = Q.front();
			Q.pop();
			for(auto v : G[cur])
				if(skoj[v] && odl[skoj[v]] == -1)
				{
					odl[skoj[v]] = 1 + odl[cur];
					Q.push(skoj[v]);
				}
		}
		for(auto v : Pan)
			odw[v] = 0;
		for(auto v : Pan)
			if(!skoj[v])
				lep |= dfs(v);
		}
	}
};
