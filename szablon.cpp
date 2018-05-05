#ifdef LOCAL
#define DBG(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#define _GLIBCXX_DEBUG
#else
#define DBG(...)
#endif

#include<bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define SZ(v) (int)((v).size())
#define pb push_back
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
const LL INF = 1e18L + 1;
const int inf = 1e9 + 1;
const LL mod=1e9+7;

using namespace std;


template<class TH> void _dbg(const char *sdbg, TH h){ cerr<<sdbg<<'='<<h<<endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg!=',')cerr<<*sdbg++;
  cerr<<'='<<h<<','; _dbg(sdbg+1, a...);
}


int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif

    return 0;
}

