struct kmp
{
	void licz(char * S, int * P)
	{
		int len = strlen(S), p = 0;
		P[0] = -1;
		P[1] = 0;
		for(int i = 2; i <= len; ++i)
		{
			while(p >= 0 && S[i - 1] != S[p])
				p = P[p];
			++p;
			P[i] = p;
		}
	}
};
