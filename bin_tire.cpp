// jest wersja trwala i zwykla

const int roz = 60; // 2 ^ roz - maksymalny rozmiar liczby

int glob[roz + 7];

struct node
{
	node * left = 0, * right = 0;
	int ile = 0;		// ile jest liczb w moim poddrzewie
	node(node * cur)
	{
		if(cur != 0)
		{
			left = cur->left;
			right = cur->right;
			ile = cur->ile;	
		}
	}
	
	node()
	{
	
	}
};

inline node * left(node * cur)
{
	if(cur == 0 || cur->left == 0)
		return 0;
	return cur->left;
}

inline node * right(node * cur)
{
	if(cur == 0 || cur->right == 0)
		return 0;
	return cur->right;
}

void add(node * cur, LL liczba) // daje zwykle (nie trwale)
{
	for(int i = 0 ;i < roz;i++)
		if(liczba & (1LL<<i))
			glob[i] = 1;
		else
			glob[i] = 0;
	int wsk = roz - 1;
	while(wsk > -1)
	{
		cur->ile++;
		if(glob[wsk] == 0)
		{
			if(cur->left == 0)
				cur->left = new node();
			cur = cur->left;
		}
		else
		{
			if(cur->right == 0)
				cur->right = new node();
			cur = cur->right;
		}
		wsk--;
	}
	cur->ile++;
}

node * dod(node * cur, int poz) // robi trwale
{
	if(poz == -1)
		return new node(cur);
	if(glob[poz] == 0)
	{
		cur = new node(cur);
		cur->left = dod(left(cur), poz - 1);
	}
	else
	{
		cur = new node(cur);
		cur->right = dod(right(cur), poz - 1);
	}
	cur->ile++;
	return cur;
}

node * add_per(node * cur, LL liczba) // robi trwale
{
	for(int i = 0 ;i < roz;i++)
		if(liczba & (1LL<<i))
			glob[i] = 1;
		else
			glob[i] = 0;
	return dod(cur, roz - 1);
}

LL maks_xor(node * cur, LL liczba) // daje maksymalnego xora
{
	LL res = 0;
	for(int i = 0 ;i < roz;i++)
		if(liczba & (1LL<<i))
			glob[i] = 1;
		else
			glob[i] = 0;
	LL pot = (1LL<<(roz - 1LL));
	node * cur2 = cur;
	int wsk = roz - 1;
	while(pot > 0)
	{
		if(glob[wsk] == 0)
		{
			if(right(cur2) != 0)
			{
				res |= pot;
				cur2 = right(cur2);
			}
			else
				cur2 = left(cur2);
			cur = left(cur);
		}
		else
		{
			if(left(cur2) != 0)
			{
				res |= pot;
				cur2 = left(cur2);
			}
			else
				cur2 = right(cur2);
			cur = right(cur);
		}
		pot >>= 1;
		wsk--;
	}
	return res;
}
