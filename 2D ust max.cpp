const int pot = 1<<17;

struct node 
{
	node * left = 0, * right = 0;
	int maxi = 0;
	
	node(int L, int P, node * le, node * ri)
	{
		left = le;
		right = ri;
	}
	
	node()
	{
	}
	
	void add(int l, int p, int xl, int xp, int val)
	{
		if(p < xl || xp < l)
			return;
		if(xl <= l && p <= xp)
		{
			maxi = max(maxi, val);
			return ;
		}
		int sr = (l + p) / 2;
		if(left == NULL)
			left = new node();
		left->add(l, sr, xl, xp, val);
		
		if(right == NULL)
			right = new node();
		right->add(sr + 1, p, xl, xp, val);
		maxi = max(maxi, val);
	}
	
	int ma(int l, int p, int a, int b)
	{
		int sr = (l + p) / 2;
		if(b < l || p < a)
			return 0;
		if(a <= l && p <= b)
			return maxi;
		return max(maxi, max(left == 0 ? 0 : left->ma(l, sr, a, b), right == 0 ? 0 : right->ma(sr + 1, p, a, b)));
	}
};

struct tree
{
	tree * left = 0, * right = 0;
	node * drze = 0;
	
	tree(int L, int P, tree * le, tree * ri, node * dr)
	{
		left = le;
		right = ri;
		drze = dr;
	}
	
	tree()
	{
	}
	
	void add(int l, int p, int x1, int x2, int y1, int y2, int val)
	{
		
		if(p < x1 || x2 < l)
			return;	
		if(drze == NULL)
			drze = new node();
		drze->add(0, pot - 1, y1, y2, val);
		if(x1 <= l && p <= x2)
			return;
		int sr = (l + p) / 2;
		if(left == NULL)
			left = new tree();
		left->add(l, sr, x1, x2, y1, y2, val);
		if(right == NULL)
			right = new tree();
		right->add(sr + 1, p, x1, x2, y1, y2, val);
	}
	
	int ma(int l, int p, int a, int b, int c, int d)
	{
		int sr = (l + p ) / 2;
		if(b < l || p < a)
			return 0;
		if(a <= l && p <= b)
			return drze->ma(0, pot - 1, c, d);
		return max(drze->ma(0, pot - 1, c, d), max(left == 0 ? 0 : left->ma(l, sr, a, b, c, d), right == 0 ? 0 : right->ma(sr + 1, p, a, b, c, d)));
	}
};
