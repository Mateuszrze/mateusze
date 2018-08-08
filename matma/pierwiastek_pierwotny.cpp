// faktoryzacja w sqrt(a)

VPLL fakt(LL a)
{
	VPLL cur;
	LL A = a;
	for(LL i = 2LL;i * i <= a;i++)
	{
		int ile = 0;
		while(A % i == 0)
		{
			A /= i;
			ile++;
		}
		if(ile > 0)
			cur.pb({i, ile});
	}	
	if(A > 1)
		cur.pb({A, 1});
	return cur;
}

// zwraca pierwiastek pierwotny modulo m

LL pierw_pierw(LL m)
{
	VPLL P = fakt(m - 1); // fakt dziala w sqrt(n) jezeli chcesz w n ^ (1/3) trzeba skopiowac funkcje fakt z rho pollarda
	while(1)
	{
		bool f = 0;
		LL kand = rand() % (m - 1) + 1;
		if(pot(kand, m - 1, m) == 1)
		{
			for(auto s : P)
				if(pot(kand, (m - 1) / s.fi, m) == 1)
				{
					f = 1;
					break;
				}
			if(f == 0)
				return kand;
		}
	}
}
