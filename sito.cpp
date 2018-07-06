#include<bits/stdc++.h>
typedef long long LL;

// sito w n loglogn

// sito dziala liniowo troche wiecej do przepisania
// ~ 2 s przy n = 1e8
// ~ 12 s przy n = 5e8
// ~ 34 s przy n = 1e9


void sito2(int * S, LL n)
{
      for(int i = 0 ;i <= n;i++)
            S[i] = 0;
      for(int i = 2 ;i <= n;i++)
            if(S[i] == 0)
                  for(int j = i;j <= n;j += i)
                        S[j] = i;
}

// sito dziala liniowo troche wiecej do przepisania
// ~ 0,7 s przy n = 1e8
// ~ 3,5 s przy n = 5e8
// ~ 8 s przy n = 1e9

void sito(int * S, LL n)
{
      LL i,p,q,x;
      for(i = 2; i <= n; i++)
            S[i] = 0;
      p = 2;
      while(p * p <= n)
      {
            q = p;
            while(p * q <= n)
            {
                  x = p * q;
                  while(x <= n)
                  {
                        S[x] = p;
                        x *= p;
                  }
                  while(S[++q] > 0);
            }
            while(S[++p] > 0);
      }
}
