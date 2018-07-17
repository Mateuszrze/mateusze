
const int MN = 105;

struct Floyd
{
	int odl[MN][MN];
	int N;
	Floyd(int n)
	{
		N = n;
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				odl[i][j] = inf;
	}
	void add_edge(int a, int b, int c)
	{
		odl[a][b] = min(odl[a][b], c);
	}
	void licz()
	{
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				for(int k = 1; k <= N; ++k)
					odl[j][k] = min(odl[j][k], odl[j][i] + odl[i][k]);
	}
};


