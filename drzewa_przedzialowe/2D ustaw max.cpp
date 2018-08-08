// pamiec - #add * log(pot)
// czas #add - log(pot)
// czas #ma - log^2(pot)

const int pot = 1<<17;

struct node
{
	node * s1 = 0, * s2 = 0, * s3 = 0, * s4 = 0;
	int xl, xp, yl, yp;
	int maxi = 0;
	// 2 1  
	// 4 3 
	node(int X1, int X2, int Y1, int Y2)
	{
		xl = X1;
		xp = X2;
		yl = Y1;
		yp = Y2;
	}
	
	node(){}
	
	
	
	
};

int ma(node * cur, int x1, int x2, int Y1, int y2) // podaj maksimum w prostokacie x1, x2, y1, y2, w drzewie o korzeniu w cur
{
	queue<node * > q;
	q.push(cur);
	int res = 0;
	while(SZ(q))
	{
		cur = q.front();
		q.pop();
		if(cur == NULL || cur->maxi <= res)
			continue;
		int xx1 = max(x1, cur->xl);
		int xx2 = min(x2, cur->xp);
		int yY1 = max(Y1, cur->yl);
		int yy2 = min(y2, cur->yp);
		if(xx2 < xx1 || yy2 < yY1)
			continue;
		if(xx1 == cur->xl && xx2 == cur->xp && yY1 == cur->yl && yy2 == cur->yp)
		{
			res = max(cur->maxi, res);
			continue;
		}
		q.push(cur->s1);
		q.push(cur->s2);
		q.push(cur->s3);
		q.push(cur->s4);
	}
	return res;
}

void add(node * cur, int x, int y, int val) // dodaj do drzewa o korzeniu cur wartosc val w punkcie x, y
{
	while(1)
	{
		cur->maxi = max(cur->maxi, val);
		if(cur->xl == cur->xp && cur->yl == cur->yp)
			return ;
		int srx = (cur->xl + cur->xp) / 2;
		int sry = (cur->yl + cur->yp) / 2;
		if(x <= srx && y <= sry)
		{
			if(cur->s4 == NULL)
				cur->s4 = new node(cur->xl, srx, cur->yl, sry);
			cur = cur->s4;
		}
		if(x > srx && y <= sry)
		{
			if(cur->s3 == NULL)
				cur->s3 = new node(srx + 1, cur->xp, cur->yl, sry);
			cur = cur->s3;
		}			
		if(x <= srx && y > sry)
		{
			if(cur->s2 == NULL)
				cur->s2 = new node(cur->xl, srx, sry + 1, cur->yp);
			cur = cur->s2;
		}
		if(x > srx && y > sry)
		{
			if(cur->s1 == NULL)
				cur->s1 = new node(srx + 1, cur->xp, sry + 1, cur->yp);
			cur = cur->s1;
		}
	}
}
	
