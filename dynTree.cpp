
const int P2 = (1 << 20);

struct Node
{
	Node *lewy = 0, *prawy = 0;
	LL suma = 0LL;
};

LL ask(Node * cur, int a, int b, int p = 0, int k = P2 - 1)
{
	if(a == p && b == k)
		return cur->suma;
	int mid = (p + k) >> 1;
	LL ret = 0LL;
	if(a <= mid && cur->lewy != 0)
		ret += ask(cur->lewy, a, min(b, mid), p, mid);
	if(b > mid && cur->prawy != 0)
		ret += ask(cur->prawy, max(a, mid + 1), b, mid + 1, k);
	return ret;
}

void add(Node * cur, int x, int v, int p = 0, int k = P2 - 1)
{
	cur->suma += v;
	if(p == k)
		return;
	int mid = (p + k) >> 1;
	if(x <= mid)
	{
		if(cur->lewy == 0)
			cur->lewy = new Node;
		add(cur->lewy, x, v, p, mid);
	}
	else
	{
		if(cur->prawy == 0)
			cur->prawy = new Node;
		add(cur->prawy, x, v, mid + 1, k);
	}
}
