
// most[i] == czy krawedz i - father[i] jest mostem
// punkt[i] == czy i jest punktem artykulacji
// low[i] == low wierzcholka i
// czas[i] == czas wejscia do i

struct mip
{
      int t;
      vector<VI> wek;
      VI low, czas, punkt, father, most;
      int n;

      mip(int N)
      {
            n = N;
            wek.resize(n + 2);
            low.resize(n + 2, 0);
            czas.resize(n + 2, 0);
            most.resize(n + 2, 0);
            punkt.resize(n + 2, 0);
            father.resize(n + 2, 0);
            t = 1;
      }

      void add_edge(int a, int b)
      {
            wek[a].pb(b);
            wek[b].pb(a);
      }

      void dfs(int x)
      {
            czas[x] = low[x] = t++;
            for(auto s : wek[x])
                  if(s != father[x])
                  {
                        if(czas[s] == 0)
                        {
                              father[s] = x;
                              dfs(s);
                              low[x] = min(low[x], low[s]);
                              if(low[s] >= czas[x] && father[x] != 0)
                                    punkt[x] = 1;
                        }
                        else
                              low[x] = min(low[x], czas[s]);
                  }
            if(low[x] == czas[x])
                  most[x] = 1;
      }

      void run()
      {
            for(int i = 1 ;i <= n;i++)
                  if(czas[i] == 0)
                  {
                        dfs(i);
                        int ile = 0;
                        for(auto s : wek[i])
                              if(father[s] == i)
                                    ile++;
                        if(ile > 1)
                              punkt[i] = 1;
                  }
      }
};
