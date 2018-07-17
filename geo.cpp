
struct punkt
{
	LL x, y;
	
	punkt(LL a, LL b) // konstruktor {a, b} dziala
	{
		x = a;
		y = b;
	}
	
	punkt operator-(const punkt a)
	{
		return punkt(x - a.x, y - a.y);
	}
	
	void operator-=(const punkt & b)
	{
		x -= b.x;
		y -= b.y;
	}
	
	bool gora() // (0, 0) jest w gorze
	{
		if(y > 0 || (y == 0 && x >= 0))
			return 1;
		return 0;
	}
	
};

LL wyz(punkt a, punkt b, punkt c) // wzraca wyznacznik 
{
	b -= a;
	c -= a;
	return b.x * c.y - b.y * c.x;
}

int wyzznak(punkt a, punkt b, punkt c) // zwraca znak wyznacznika
{
	LL res = wyz(a, b, c);
	if(res > 0)
		return 1;
	if(res == 0)
		return 0;
	return -1;
}

LL skalar(punkt a, punkt b) // iloczn skalarny
{
	return a.x * b.x + a.y * b.y;
}

bool angcomp(punkt & a, punkt & b) // komparator do sortowania katowego
{
	if(a.gora() != b.gora())
		return b.gora() < a.gora();
	return wyzznak(punkt(0, 0), a, b) == 1; 
}
