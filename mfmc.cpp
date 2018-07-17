
const int MN = 105;

struct MFMC
{

int K[MN][MN], F[MN][MN], C[MN][MN];
int odl[MN], poprz[MN], jest[MN];

vector < int > G[MN];

int N;

void add_edge(int a, int b, int c, int f)
{
	G[a].pb(b);
	G[b].pb(a);
	C[a][b] = f;
	K[a][b] = c, K[b][a] = -c;
}	

void spfa(int s)
{
	for(int i = 1; i <= N; ++i)
		poprz[i] = 0, odl[i] = inf;
	odl[s] = 0;
	queue < int > Q;
	Q.push(s);
	while(!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		jest[cur] = 0;
		for(auto x : G[cur])
		{
			if(odl[x] > odl[cur] + K[cur][x] && C[cur][x] - F[cur][x] > 0)
			{
				poprz[x] = cur;
				odl[x] = odl[cur] + K[cur][x];
				if(!jest[x])
				{
					Q.push(x);
					jest[x] = 1;
				}
			}
		}
	}
}

int flow(int s, int t)
{
	while(1)
	{
		spfa(s);
		if(odl[t] == inf)
			break;
		int cur = t;
		int pcham = inf;
		while(poprz[cur])
		{
			pcham = min(pcham, C[poprz[cur]][cur] - F[poprz[cur]][cur]);
			cur = poprz[cur];
		}
		cur = t;
		while(poprz[cur])
		{
			F[poprz[cur]][cur] += pcham;
			F[cur][poprz[cur]] -= pcham;
			cur = poprz[cur];
		}
		
	}
	int res = 0;
	for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			if(F[i][j] > 0)
				res += koszt[i][j];
	return res;
}

};


