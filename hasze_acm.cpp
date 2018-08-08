
struct hasze
{
      vector<int> wyk, pref, odw;
      LL mod = 1e9 + 7; /////////////////////// tutaj wstawic modulo
      string s;
      LL pot(LL a, LL w)
      {
            if(w == 0)
                  return 1;
            LL b = pot(a, w / 2);
            b *= b;
            b %= mod;
            if(w & 1LL)
                  b = (b * a) % mod;
            return b;
      }

      hasze(string S)
      {
            s = S;
            wyk.pb(1);
            wyk.pb(2137); /////////////////////// tutaj wstawic podstawe
            for(int i = 2 ;i < SZ(s);i++)
                  wyk.pb((wyk.back() * (LL)wyk[1]) % mod);
            for(int i = 0 ;i < SZ(s);i++)
                  pref.pb(( (LL)(i == 0 ? 0 : pref.back()) + wyk[i] * (LL)s[i]) % mod);
            odw.pb(1);
            odw.pb(pot(wyk[1], mod - 2)); // tuaj wstawic odwrotnosc wyk[1]
            for(int i = 2 ;i < SZ(s);i++)
                  odw.pb((odw.back() * (LL)odw[1]) % mod);
      }

      LL hasz(int l, int p)
      {
            if(l == 0)
                  return pref[p];
            return ((pref[p] - pref[l - 1] + mod) * (LL)odw[l]) % mod;
      }
};

