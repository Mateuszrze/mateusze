const int P2 = (1 << 20);

struct Node
{
	Node * le, * pr;
	int suma;
	Node()
	{
		le = pr = 0;
		suma = 0;
	}
};

int suma(Node * x) {
	return (x == 0 ? 0 : x->suma); }

Node * le(Node * x) {
	return (x == 0 ? 0 : x->le); }

Node * pr(Node * x) {
	return (x == 0 ? 0 : x->pr); }

Node * add(Node * cur, int val = 0, int pos = 0, int l = 0, int r = P2) //podajemy : korzen, wartosc, pozycja
{
	Node * ret = new Node;
	ret->le = le(cur), ret->pr = pr(cur);
	if(l == r)
	{
		ret->suma = val + suma(cur);
		return ret;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)
		ret->le = add(le(cur), val, pos, l, mid);
	else
		ret->pr = add(pr(cur), val, pos, mid + 1, r);
	ret->suma = suma(le(ret)) + suma(pr(ret));
	return ret;
}

int ask(Node * cur, int a, int b, int l = 0, int r = P2) //podajemy: korzen, pocz, kon przedzialu
{
	if(a == l && b == r)
		return suma(cur);
	int ret = 0, mid = (l + r) >> 1;
	if(a <= mid)
		ret += ask(le(cur), a, min(b, mid), l, mid);
	if(b > mid)
		ret += ask(pr(cur), max(a, mid + 1), b, mid + 1, r);
	return ret;
}

