// nie testowane
const int maxn = 1e6 + 7;

struct cen
{
  int n;
  vector<int> wek[maxn];
  int r[maxn];
  bool zaz[maxn];
  vector<int> stos;
  int najw[maxn];

  cen()
  {
    n = 0;
    for(int i = 0;i < maxn;i++)
    {
      zaz[i] = 0;
      r[i] = 0;
      wek[i].clear();
    }
  }

  void add_edge(int a, int b)
  {
    wek[a].pb(b);
    wek[b].pb(a);
  }

  void d(int x, int f)
  {
    r[x] = 1;
    najw[x] = 0;
    for(auto s : wek[x])
      if(s != f && zaz[s] == 0)
      {
        d(s, x);
        r[x] += r[s];
        najw[x] = max(najw[x], r[s]);
      }
    stos.pb(x);
  }

  int kto(int x)
  {
    stos.clear();
    d(x, -1);
    for(auto s : stos)
      if(najw[s] * 2 <= r[x] && (r[x] - r[s]) * 2 <= r[x])
        return s;
    assert(0);
  }

  void centro(int x, int poz = 1)
  {
    x = kto(x);
    // x to centroid rob co chcesz
    zaz[x] = 1;
    for(auto s : wek[x])
      if(zaz[s] == 0)
        centro(s, poz + 1);
  }

};
