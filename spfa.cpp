

vector < PII > G[MN];

struct spfa
{

queue < int > Q;
int jest[MN], poprz[MN];

int Path(int s, int N, int * odl)
{
	for(int i = 1; i <= N; ++i)
		poprz[i] = 0, odl[i] = inf;
	odl[s] = 0;
	Q.push(s);
	while(!Q.empty())
	{
		int cur = Q.front();
		Q.pop();
		jest[cur] = 0;
		for(auto x : G[cur])
		{
			if(odl[x.fi] > odl[cur] + x.se)
			{
				poprz[x.fi] = cur;
				odl[x.fi] = odl[cur] + x.se;
				if(!jest[x])
				{
					Q.push(x);
					jest[x] = 1;
				}
			}
		}
	}
}

};
