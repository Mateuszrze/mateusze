
struct matrix
{
  static const int roz = 102;
  static const LL mod = 1e9 + 7;
  LL tab[roz][roz];

  matrix(LL val = 0LL)
  {
    for(int i = 0 ;i < roz;i++)
      for(int j = 0;j < roz;j++)
        tab[i][j] = 0;
    for(int i = 0 ;i < roz;i++)
      tab[i][i] = val;
  }

  void ogar()
  {
    for(int i = 0 ;i < roz;i++)
      for(int j = 0; j < roz;j++)
        tab[i][j] %= mod;
  }

  matrix operator*(const matrix & a)const
  {
    matrix res;
    for(int i = 0;i < roz;i++)
      for(int j = 0 ;j < roz;j++)
        for(int k = 0 ;k < roz;k++)
        {
            res.tab[i][k] += tab[i][j] * a.tab[j][k];
            if(res.tab[i][k] >= mod * mod)
              res.tab[i][k] -= mod * mod;
            if(res.tab[i][k] <= - mod * mod)
              res.tab[i][k] += mod * mod;
        }
    for(int i = 0;i < roz;i++)
      for(int j = 0 ;j < roz;j++)
        res.tab[i][j] %= mod;
    return res;
  }
};

matrix pot(matrix cur, LL wyk)
{
  if(wyk == 0)
    return matrix(1);
  matrix cnt = pot(cur, wyk / 2LL);
  cnt = cnt * cnt;
  if(wyk & 1)
    cnt = cnt * cur;
  return cnt;
}
