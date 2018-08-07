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
