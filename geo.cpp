
const LD eps = 1e-9;

typedef long long D;
const LD PI = acos(-1);

struct point
{
  D x, y;
  point(D X = (D)0,D Y = (D)0) : x(X), y(Y){}
  point operator-(point & a){return point(x - a.x, y - a.y);}
  point operator+(point & a){return point(x + a.x, y + a.y);}
  point operator+=(point & a){x += a.x; y += a.y; return *this;}
  point operator-=(point & a){x -= a.x; y -= a.y; return *this;}
  LD kat(){return atan2(y, x);}
  LD kat_dodatni(){LD res = atan2(y, x); if(res < -eps) res += 2.0 * PI; return res;}
  LD dist(point a){return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));}
  point operator*(LD val){return point(x * val, y * val);}
};

// zwraca kat skierowany miedzy wektorami a oraz b (od a do b)

LD kat(point a, point b)
{
  LD res = b.kat() - a.kat();
  if(res < -eps)
    res += 2 * PI;
  return res;
}

// zwraca iloczyn wektorowy
D wyz(point a, point b, point c)
{
  b -= a;
  c -= a;
  return b.x * c.y - b.y * c.x;
}

// zwraca znak iloczynu wektorowego
int wyzznak(point a, point b, point c)
{
  D res = wyz(a, b, c);
  if(res > 0)
    return 1;
  if(res < 0)
    return -1;
  return 0;
}

// zwraca pole wielokata (mozliwe ze wkleslego)
LD pole(vector<point> V)
{
  D res = (D)0;
  V.pb(V[0]);
  for(int i = 0;i + 1 < SZ(V);i++)
    res += wyz(point(0, 0),V[i], V[i + 1]);
  return abs(res / (LD)2.0);
}

struct line
{
  D A, B, C;
  line(D a, D b, D c) : A(a), B(b), C(c){}
  line(){A = B = C = (D) 0;}
  line(point a, point b, bool f = 0) // f = 0 - prosta ma przechodzic przez punkty a i b, f = 1 - prosta ma postac a + t * b dla t rzeczywitego
  {
    if(f == 0)
    {
      B = b.x - a.x;
      A = a.y - b.y;
      C = a.y * (a.x - b.x) + a.x * (b.y - a.y);
    }
    else
    {
      A = b.x;
      B = b.y;
      C = -(a.x * b.x + a.y * b.y);
    }
  }
  // zwraca dwa punkty lezace na prostej
  pair<point, point> punkty()
  {
    if(fabs(A) < eps)
      return {point((D)0, -C / B), point((D)1, -(C + A) / B)};
    return {point(-C / A, (D)0), point(-(C + B) / A, (D)1)};
  }
};

// odleglosc punktu a od prostej b
LD dist(point a, line b)
{
  return abs((b.A * a.x + b.B * a.y + b.C) / (LD)sqrt(b.A * b.A + b.B * b.B));
}

//odleglosc punktu p od odcinka o koncach w a oraz b

// punkt przeciecia dwoch prostych
point inter(line a, line b)
{
	if(fabs(a.A * b.B - a.B * b.A) < eps)// uwaga na to //////////////////////////////////////
		return {(D)1e18, (D)1e18}; // te proste sie nie przecinaja
	return point((b.B * a.C - a.B * b.C ) / (LD)(b.A * a.B - a.A * b.B), (b.A * a.C - a.A * b.C) / (LD)(a.A * b.B - b.A * a.B));
}

// rzut punktu a na prosta b
point rzut(point a, line b)
{
  line dwa(-b.B, b.A, b.B * a.x - a.y * b.A);
  return inter(b, dwa);
}

//odleglosc punktu p od odcinka a, b
LD point_segment_dist(point p, point a, point b)
{
  point cnt = rzut(p, line(a, b));
  if(fabs(cnt.dist(a) + cnt.dist(b) - a.dist(b)) < eps)
    return dist(p, line(a, b));
  return min(p.dist(a), p.dist(b));
}

//odleglosc punktu p od polprostej o rownaniu a + t * b dla t >= 0
LD point_halfline_dist(point p, point a, point b)
{
  LD cnt = point_segment_dist(p, a, b);
  if(p.dist(a) > p.dist(b))
    return dist(p, line(a, b));
  return cnt;
}

//czy odcinki a, b oraz c, d sie przecinaja
bool przecinanie(point a, point b, point c, point d)
{
  int A = wyzznak(a, c, d);
  int B = wyzznak(b, c, d);
  int C = wyzznak(c, a, b);
  int DD = wyzznak(d, a, b);
  return ((A != B || A == 0) && (C != DD || C == 0));
}

// najmniejsza odleglosc miedzy punktem z odinka a, b oraz odcinka c, d
LD segment_segment_dist(point a, point b, point c, point d)
{
  if(przecinanie(a, b, c, d))
    return (LD) 0.0;
  LD res = a.dist(c);
  for(auto s : {a, b})
    for(auto v : {c, d})
      res = min(res, s.dist(v));
  res = min(res, point_segment_dist(a, c, d));
  res = min(res, point_segment_dist(b, c, d));
  res = min(res, point_segment_dist(c, a, b));
  res = min(res, point_segment_dist(d, a, b));
  return res;
}

// zwraca dwie proste obie sa odlegle o dokladnie R od a
pair<line, line> line_dist(line a, LD R)
{
  point xd = a.punkty().fi;
  line cnt(a.A, a.B, R * sqrt(a.A * a.A + a.B * a.B) - a.A * xd.x - a.B * xd.y);
  line cnt2(cnt.A, cnt.B, -R * sqrt(a.A * a.A + a.B * a.B) - a.A * xd.x - a.B * xd.y);
  return {cnt, cnt2};
}

// odleglosc miedzy polprosta a + t * b oraz c + r * d, dla t, r >= 0
LD halfseg_halfseg_dist(point a, point b, point c, point d)
{
  LD res = point_halfline_dist(a, c, d);
  res = min(res, point_halfline_dist(c, a, b));
  point e = inter(line(a, b), line(c, d));
  if(point_halfline_dist(e, a, b) < eps && point_halfline_dist(e, c, d) < eps)
    return (LD) 0.0;
  return res;
}
