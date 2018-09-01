
// V[i] - wierzcholki ktore leza na sciezce o numerze i w kolejnosci rosnacej glebokosci
// deep[i] - glebokosc wierzcholka i
// chain[i] - numer sciezki na ktorej lezy wierzcholek i
// naj[i] - rozmiar najciezszego syna wierzcholka i
// kto[i] - najciezszy syn wierzcholka i
// pos[i] - pozycja w drzewie na ktorej stoi i

struct segtree
{
      vector<int> tree;
      int pot = 1;


      void ust(int x)
      {
            while(pot <= x)
                  pot *= 2;
            tree.resize(2 * pot + 7, 0);
      }

      segtree(int N = 0)
      {
            ust(N);
      }

      void ust(int x, int val)
      {
            x += pot;
            tree[x] = val;
            x /= 2;
            while(x > 0)
            {
                  tree[x] = max(tree[2 * x], tree[2 * x + 1]);
                  x /= 2;
            }
      }

      int maxi(int l, int p)
      {
            int res = 0;
            l += pot;
            p += pot;
            while(l <= p)
            {
                  if(l & 1)
                        res = max(res, tree[l]);
                  if(!(p& 1))
                        res = max(res, tree[p]);
                  l = (l + 1) / 2;
                  p = (p - 1) / 2;
            }
            return res;
      }

};

// tutaj sie zaczyna wlasciwe hld

struct hld
{
      vector< vector<int> > wek, V; // wek - wektor ktory robi graf
      vector< vector<pair<int, int > > > G;
      int n;
      int root = 1;
      vector<int> deep, f, chain, r, naj, kto, pos;
      int wolne = 2;
      segtree drze;

      hld(int N, int ROOT = 1)
      {
            n = N;
            wek.resize(n + 1);
            G.resize(n + 1);
            pos.resize(n + 1, 0);
            deep.resize(n + 1, 0);
            f.resize(n + 1, 0);
            chain.resize(n + 1, 0);
            r.resize(n + 1, 0);
            V.resize(n + 1);
            naj.resize(n + 1, 0);
            kto.resize(n + 1, 0);
            root = ROOT;
            drze.ust(N);
      }

      void add_edge(int a, int b, int c)
      {
            wek[a].pb(b);
            wek[b].pb(a);
            G[a].pb({b, c});
            G[b].pb({a, c});
      }

      void dfs(int x)
      {
            r[x] = 1;
            for(auto s : wek[x])
                  if(s != f[x])
                  {
                        f[s] = x;
                        deep[s] = deep[x] + 1;
                        dfs(s);
                        r[x] += r[s];
                        if(r[s] > naj[x])
                        {
                              naj[x] = r[s];
                              kto[x] = s;
                        }
                  }
      }

      void dfs2(int x, int num)
      {
            V[num].pb(x);
            chain[x] = num;
            for(auto s : wek[x])
                  if(s != f[x])
                  {
                        if(s == kto[x])
                              dfs2(s, num);
                        else
                        {
                              wolne++;
                              assert(r[x] >= 2 * r[s]);
                              dfs2(s, wolne - 1);
                        }
                  }
      }

      void run()
      {
            dfs(root);
            dfs2(root, 1);
            int cnt = 1;
            for(int i = 1 ;i < wolne;i++)
            {
                  for(auto s : V[i])
                        pos[s] = cnt++;
            }
            // tutaj trzeba ustawic wartosci startowe
            for(int i = 1; i <= n;i++)
                  for(auto s : G[i])
                        if(s.fi == f[i])
                              drze.ust(pos[i], s.se);
      }

      int lca(int a, int b) // zwraca lca dla dwoch wierzcholkow
      {
            while(chain[a] != chain[b])
            {
                  if(deep[V[chain[a]][0]] < deep[V[chain[b]][0]])
                        swap(a, b);
                  a = f[V[chain[a]][0]];
            }
            return deep[a] < deep[b] ? a : b;
      }

      int odl(int a, int b) // zwraca odleglosc miedzy dwoma wierzcholkami
      {
            return deep[a] + deep[b] - 2 * deep[lca(a, b)];
      }

      int maxi(int a, int b)
      {
            int res = 0;
            while(chain[a] != chain[b])
            {
                  if(deep[V[chain[a]][0]] < deep[V[chain[b]][0]])
                        swap(a, b);
                  // tutaj skaczemy z wierzcholka a do ojca sciezki a przedzial w drzewie to pos[V[chain[a]][0]], pos[a]
                  res = max(res, drze.maxi(pos[V[chain[a]][0]], pos[a]));
                  a = f[V[chain[a]][0]];
            }
            if(deep[a] > deep[b])
                  swap(a, b);
            // jezeli chcemy takze wziac wartosc w lca trzeba dac (pos[a], pos[b]);
            res = max(res, drze.maxi(pos[a] + 1, pos[b])); // tutaj uzupelniamy to co jest na sciezce na ktorej teraz lezy a i b - uzupelniamy odcinek  ( pozycja a, pozycja b >
            return res;
      }
};
