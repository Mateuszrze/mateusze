

struct kmp
{
	void licz(char * S, int * P)
	{
		int len = strlen(S), p = 0;
		P[0] = -1;
		for(int i = 1; i < len; ++i)
		{
			while(p >= 0 && S[i] != S[p])
				p = P[p];
			++p;
			P[i] = p;
		}
	}
};

