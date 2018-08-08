
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

// zwraca funkcje kajmajkla od a

LL karma(LL a)
{
	VPLL cnt = fakt(a); // fakt dziala w sqrt(n) jezeli chcesz w n ^ (1/3) trzeba skopiowac funkcje fakt z rho pollarda
	LL cur = 1LL;
	for(auto s : cnt)
	{
		LL xd = 1LL;
		for(int i = 1 ;i < s.se;i++)
			xd *= s.fi;
		xd *= s.fi - 1;	
		cur = cur * xd / __gcd(cur, xd);
	}
	return cur;
}

//zwraca fi od a

LL fi(LL a)
{
	VPLL cnt = fakt(a); // fakt dziala w sqrt(n) jezeli chcesz w n ^ (1/3) trzeba skopiowac funkcje fakt z rho pollarda
	LL cur = 1LL;
	for(auto s : cnt)
	{
		for(int i = 1 ;i < s.se;i++)
			cur *= s.fi;
		cur *= s.fi - 1;	
	}
	return cur;
}
