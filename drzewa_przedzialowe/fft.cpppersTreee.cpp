
struct Node
{
	Node *le = 0, *pr = 0;
	LL suma = 0LL;
};

struct PT
{

inline LL suma(Node *x)
{
	if(!x)
		return 0LL;
	return x->suma;
}

inline Node *le(Node *x)
{
	if(!x)
		return 0;
	return x->le;
}

inline Node *pr(Node *x)
{
	if(!x)
		return 0;
	return x->pr;
}

//wierzcholek akt, wierzcholek poprzedni, jego pocz, jego kon, gdzie, co dodaje
void add(Node *cur, Node *ost, int a, int b, int p, LL v) 
{
	if(a == b)
	{
		cur->suma = suma(ost) + v;
		return;
	}
	int mid = (a + b) >> 1;
	if(p <= mid)
	{
		cur->le = new Node;
		cur->pr = pr(ost);
		add(cur->le, le(ost), a, mid, p, v);
	}
	else
	{
		cur->le = le(ost);
		cur->pr = new Node;
		add(cur->pr, pr(ost), mid + 1, b, p, v);
	}
	cur->suma = suma(cur->le) + suma(cur->pr);
}

//wierzcholek jego pocz, jego kon, pocz pytania, kon pytania

LL ask(Node *cur, int a, int b, int p, int k)

{
	if(a == p && b == k)
		return suma(cur);
	int mid = (a + b) >> 1;
	LL ret = 0LL;
	if(p <= mid)
		ret += ask(le(cur), a, mid, p, min(mid, k));
	if(k > mid)
		ret += ask(pr(cur), mid + 1, b, max(p, mid + 1), k);
	return ret;
}

};

