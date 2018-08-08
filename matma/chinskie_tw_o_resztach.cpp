// rozszezony euklides
PLL euk(LL a, LL b)
{
      if(a > b)
      {
            PLL x = euk(b, a);
            return {x.se, x.fi};
      }
      if(a == 0)
            return {0, 1};
      PLL x = euk(b % a, a);
      return {(x.se - x.fi * (b / a)), x.fi};
}

// rozwiazuje uklad x przystaje do a.fi mod a.se
// x przystaje do b.fi mod b.se
// zwaraca pare c taka ze: x przysate do c.fi mod c.se

pair < LL, LL > dwie_kongr(pair < LL, LL> a, pair < LL, LL > b)
{
	pair < LL, LL > e = euk(a.se, b.se);
	LL nwd = a.se * e.fi + b.se * e.se;
	LL nww = a.se / nwd * b.se;
	LL roz = (nww + b.fi - a.fi) % nww;
	if (roz % nwd != 0LL)
		return {0LL, 0LL};
	LL t = a.fi % nwd;
	a.fi /= nwd, b.fi /= nwd;
	LL ans = (e.fi * a.se * b.fi + e.se * b.se * a.fi + t ) % nww;
	ans = (ans + nww ) % nww;
	return {ans, nww};
}

//{2, 3} -> x przystaje do 2 mod 3
// zwraca pare x przystaje do a.fi modulo a.se
pair < LL, LL> uklad_kongr(const vector < pair < LL ,LL > >& V)
{
	assert(V.size() > 0);
	pair < LL, LL > ans = V[0];
	for(int i = 1; i < SZ(V); i++)
	{
		ans = dwie_kongr(ans, V[i]);
		if (ans.se == 0LL)
			return make_pair(0LL, 0LL); 
	}
	return ans;
}
