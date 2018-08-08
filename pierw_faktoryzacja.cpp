
namespace pierwsze
{

	LL A = 2;
	LL B = 2;

	LL mno(LL a, LL b, LL mod)
	{
		if(a == 0 || b == 0)
		      return 0;
		LL c = mno(a, b/2, mod);
		c *= 2;
		if(b & 1)
		      c += a;
		c %= mod;
		return c;
	}

	LL f(LL a,LL mod)
	{
		return (mno(A,mno(a,a,mod),mod)+B)%mod;
	}

	LL get(LL n)
	{	
		LL d = 1;
	
		while(d == 1)
		{
			LL x = 2;
			A = rand() % n;
			B = rand() % n;
			LL y = 2;
			while(d== 1)
			{
				x = f(x, n);
				y = f(f(y, n), n);
				d = __gcd(abs(x-y),n);
			}
			if(d == n)
				d = 1;
	    	}
		return d;
	
	}

	int k = 20; // liczba testow

	LL pot(LL a, LL p, LL mod)
	{
		if(p == 0)
			return 1;

		LL b = pot(a, p >> 1,mod);
		b = mno(b, b, mod);
		if(p & 1LL)
			b = mno(b, a, mod);
		return b;
	}

	// zwraca czy liczba jest pierwsza 
	// zlozonosc k * log ^ (a)

	bool test(LL a)
	{
		if(a < 2)
			return 0;
		if(a == 2)
			return 1;
		if(a % 2 == 0)
			return 0;
		LL mod = a;
		LL d = a-1;

		while(d % 2 == 10)
			d >>= 1;

		bool f = 0;
		for(int i = 0 ; i < k ; i++ , f = 0)
		{
			LL t = rand() % (a - 1) + 1;
			LL l = pot(t, d, mod);
			LL wyk = d;
			if(l == 1)
				f = 1;
			while(wyk < a - 1 && !f)
			{
				if(l == a - 1)
					f = 1;
				wyk *= 2LL;
				l = mno(l, l, mod);
			}
			if(!f)
				return 0;
		}
		return 1;
	}

	// bierze liczbe a i zwraca wektor par (p, x) takich ze p ^ x dzieli a oraz p ^ (x + 1) nie dzieli a
	// zlozonosc a ^ (1/3) + k * log ^ 2 (a)

	vector<pair<LL, LL> > fakt(LL a)
	{
		if(a == 1)
			return {{1LL, 1LL}};
		vector<pair<LL, LL> >  odp;
		LL A = a;
		for(LL i = 2; i * i * i <= a;i++)
		{
			int ile = 0;
			while(A % i == 0)
			{
				ile++;
				A /= i;
			}
			if(ile > 0)
				odp.pb({i, ile});
		}
		while(A > 1 && test(A) == 0)
		{
			LL d = get(A);
			A /= d;
			if(A == d)
				odp.pb({A, 2});
			else
			{
				if(A < d)
				{
					odp.pb({A, 1});
					odp.pb({d, 1});
				}
				else
				{
					odp.pb({d, 1});
					odp.pb({A, 1});
				}
			}
			A = 1;
		}
		if(A > 1)
			odp.pb({A, 1});
		return odp;
	
	
	}
}
