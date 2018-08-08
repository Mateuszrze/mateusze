#define point complex<LD>
#define x real()
#define y imag()

bool gora(point a)
{
	if(a.y > eps || (a.y >= eps && a.x >= eps))
		return 1;
	return 0;
}

LD wyz(point a, point b, point c) // wzraca wyznacznik 
{
	b -= a;
	c -= a;
	return b.x * c.y - b.y * c.x;
}

int wyzznak(point a, point b, point c) // zwraca znak wyznacznika
{
	LL res = wyz(a, b, c);
	if(res > 0)
		return 1;
	if(res == 0)
		return 0;
	return -1;
}

LD skalar(point a, point b) // iloczn skalarny
{
	return a.x * b.x + a.y * b.y;
}

bool angcomp(point & a, point & b) // komparator do sortowania katowego
{
	if(gora(a) != gora(b))
		return gora(b) < gora(a);
	return wyzznak(point(0, 0), a, b) == 1; 
}

struct line
{
	LD a, b, c;
	
	line(LD A, LD B, LD C)
	{
		a = A;
		b = B;
		c = C;
	}
	
	line(point A, point B)
	{
		a = A.y - B.y;
		b = B.x - A.x;
		c = A.y * (A.x - B.x) + (B.y - A.y) * A.x;
	}

};

// punktprzeciecia dwoch prostych
point inter(line a, line b)
{
	if(fabs(a.a * b.b - a.b * b.a) < eps)// uwaga na to //////////////////////////////////////
		return {1e18, 1e18}; // te proste sie nie przecinaja
	return {(b.b * a.c - a.b * b.c ) / (b.a * a.b - a.a * b.b), (b.a * a.c - a.a * b.c) / (a.a * b.b - b.a * a.b)};
}

bool com(point a, point b)
{
	if(a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

// zwraca otoczke wypukla zbioru punktow cur
// uwaga na zmiennoprzecinkowe 

vector<point> rob(vector<point> cur)
{
	sort(all(cur), com);
	vector<point> oto;
	for(auto s : cur)
	{
		while(SZ(oto) >= 2 && wyzznak(oto[SZ(oto) - 2], oto.back(), s) <= 0)
			oto.pop_back();
		oto.push_back(s);
	}
	reverse(all(cur));
	vector<point> oto2;
	for(auto s : cur)
	{
		while(SZ(oto2) >= 2 && wyzznak(oto2[SZ(oto2) - 2], oto2.back(), s) <= 0)
			oto2.pop_back();
		oto2.push_back(s);
	}
	for(int i = 1; i < SZ(oto2) - 1;i++)
		oto.pb(oto2[i]);	
	return oto;
}
