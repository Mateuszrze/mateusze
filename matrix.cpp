
const int mod = 1000000007;
const int MN = 105;


struct matrix
{
	LL V[MN][MN];
	matrix(LL prz = 1LL)
	{
		for(int i = 0; i < MN; ++i)
			for(int j = 0; j < MN; ++j)
				V[i][j] = 0LL;
		for(int i = 0; i < MN; ++i)
			V[i][i] = prz;
	}
	matrix operator*(matrix & m)
	{
		matrix wyn(0LL);
		for(int i = 0; i < MN; ++i)
			for(int j = 0; j < MN; ++j)
				for(int k = 0; k < MN; ++k)
				{
					wyn.V[i][j] += V[i][k] * m.V[k][j];
					wyn.V[i][j] %= mod;
				}
		return wyn;
	}
	matrix operator^(LL wyk)
	{
		matrix wyn(1LL), tmp = (*this);
		while(wyk)
		{
			if(wyk & 1LL)
				wyn = wyn * tmp;
			tmp = tmp * tmp;
			wyk >>= 1;
		}
		return wyn;
	}
};


int main()	
{
	return 0;
}
