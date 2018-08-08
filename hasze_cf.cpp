
struct hasze
{
      vector<int> wyk, pref, odw;
      VLL potpot = {5003, 5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087, 5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171};
      VLL modmod = {999999929, 999999937, 1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000103, 1000000123, 1000000181, 1000000207, 1000000223, 1000000241, 1000000271, 1000000289, 1000000297, 1000000321, 1000000349};
      static LL mod;//1e9 + 7; /////////////////////// tutaj wstawic modulo
      static LL POT;
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
      	srand((LL) new int);
      	if(mod == 0)
      	{
      		POT = potpot[rand() % SZ(potpot)];
      		mod = modmod[rand() % SZ(modmod)];
      	}
      	s = S;
            wyk.pb(1);
            wyk.pb(POT); /////////////////////// tutaj wstawic podstawe
            for(int i = 2 ;i < SZ(s);i++)
                  wyk.pb((wyk.back() * (LL)wyk[1]) % mod);
            for(int i = 0 ;i < SZ(s);i++)
                  pref.pb(( (LL)(i == 0 ? 0 : pref.back()) + wyk[i] * (LL)s[i]) % mod);
            odw.pb(1);
            odw.pb(pot(wyk[1], mod - 2));
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

LL hasze::mod = 0;
LL hasze::POT = 0;
