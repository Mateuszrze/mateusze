
namespace MCF {
  #define MAXN 100010
  #define MAXM 2000010
  #define wint int
  #define cint int
  const wint wEPS = 0;
  const wint wINF = 1001001001;
  const cint cEPS = 0;
  const cint cINF = 1001001001;
  int n, m, ptr[MAXN], nxt[MAXM], zu[MAXM];
  wint capa[MAXM], tof;
  cint cost[MAXM], toc, d[MAXN], pot[MAXN];
  int vis[MAXN], pree[MAXN];
  void init(int _n) {
    n = _n+2;
    m = 0;
    memset(ptr, ~0, n << 2);
  }
  void ae(int u, int v, wint w, cint c) {
    //cerr << u << " " << v << " " << c << "\n";
    nxt[m] = ptr[u]; ptr[u] = m; zu[m] = v; capa[m] = w; cost[m] = +c; ++m;
    nxt[m] = ptr[v]; ptr[v] = m; zu[m] = u; capa[m] = 0; cost[m] = -c; ++m;
  }
  bool spRep(int src, int ink, wint flo = wINF) {
    wint f;
    cint c, cc;
    int i, v;
    memset(pot, 0, n  * sizeof(cint));
    for(bool cont = 1; cont; ) {
      cont = 0;
      for(int u=0; u<n; u++) for(i=ptr[u]; ~i; i = nxt[i]) if(capa[i] > wEPS) {
        if (pot[zu[i]] > pot[u] + cost[i] + cEPS) {
          pot[zu[i]] = pot[u] + cost[i]; cont = 1;
        }
      }
    }
    for(toc = 0, tof = 0; tof + wEPS < flo; ) {
      typedef pair <cint, int> node;
      priority_queue <node, vector <node>, greater<node> > q;
      for(int u=0; u<n; u++) { d[u] = cINF; vis[u] = 0; }
      for(q.push(make_pair(d[src] = 0, src)); !q.empty(); ) {
        c = q.top().first; int u = q.top().second; q.pop();
        if(vis[u]++) continue;
        for(i = ptr[u]; ~i; i = nxt[i]) if(capa[i] > wEPS) {
          cc = c + cost[i] + pot[u] - pot[v = zu[i]];
          if(d[v] > cc) { q.push(make_pair(d[v] = cc, v)); pree[v] = i; }
        }
      }
      if(!vis[ink]) return 0;
      f = flo - tof;
      for(v = ink; v != src; v = zu[i^1]) { i = pree[v]; f = min(f, capa[i]); }
      for(v = ink; v != src; v = zu[i^1]) { i = pree[v]; capa[i] -= f; capa[i^1] += f; }
      tof += f;
      toc += f * (d[ink] - pot[src] + pot[ink]);
      for(int u=0; u<n; u++) pot[u] += d[u];
    }
    return 1;
  }
}
