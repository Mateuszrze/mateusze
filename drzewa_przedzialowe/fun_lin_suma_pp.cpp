
// dodaj funkcje liniowa na przedziale 
// suma na przedziale 

const int P = 1<<20;

LL pocz[2 * P + 7], post[2 * P + 7], suma[2 * P + 7];

LL ciag(LL pocz, LL d, LL dl)
{
      return ((pocz + (dl - 1LL) * d + pocz) * dl) / 2LL;
}

inline void update(int cur, LL dl)
{
      if(dl == 1)
            suma[cur] = ciag(pocz[cur], post[cur], dl);
      else
            suma[cur] = suma[2 * cur] + suma[2 * cur + 1] + ciag(pocz[cur], post[cur], dl);
}

void propag(int cur, LL dl)
{
      assert(dl % 2 == 0);
      pocz[2 * cur] += pocz[cur];
      post[2 * cur] += post[cur];
      pocz[2 * cur + 1] += pocz[cur] + post[cur] * (dl / 2 );
      post[2 * cur + 1] += post[cur];
      pocz[cur] = post[cur] = suma[cur] = 0LL;
      update(2 * cur, dl / 2);
      update(2 * cur + 1, dl / 2);
      update(cur, dl);

}

void add(int l, int p, LL st, LL d, LL lewo, LL prawo, int cur)
{
      if(lewo > p || prawo < l)
            return ;
      if(l <= lewo && prawo <= p)
      {
            pocz[cur] += (lewo - l) * d + st;
            post[cur] += d;
            update(cur, prawo - lewo + 1);
            return;
      }
      int sr = (lewo + prawo ) / 2;
      add(l, p, st, d, lewo , sr, 2 * cur);
      add(l, p, st, d, sr + 1, prawo, 2 * cur + 1);
      update(cur, prawo - lewo + 1);
}

LL sum(int l, int p, LL lewo, LL prawo, int cur)
{
      if(lewo > p || prawo < l)
            return 0LL;
      if(l <= lewo && prawo <= p)
            return suma[cur];
      propag(cur, prawo - lewo + 1);
      int sr = (lewo + prawo ) / 2;
      return sum(l, p, lewo, sr, 2 * cur) + sum(l, p, sr + 1, prawo, 2 * cur + 1);
}
