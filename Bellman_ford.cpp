// kto zna Bellmana_forda ten spoko morda

struct bel_ford
{
	vector<pair<PII, LL> > graf;
	vector<LL> odl; // w tej tablicy znajduja sie odleglosci po uruchomieniu funkcji run
	// jezeli odl[i] >= LLinf / 2 to znaczy ze wierzcholek jest nieosiagalny
	bool f = 0; // czy jest cykl ujemny
	int n = 0; // rozmiar grafu - najwiekszy wierzcholek
	
	void add_edge(int a, int b, LL c, bool flag = 1) // jezeli f == 1 to krawedz jest nieskierowana
	{
		n = max(a, n);
		n = max(b, n);
		graf.pb({{a, b}, c});
		if(flag)
			graf.pb({{b, a}, c});
	}
	
	void run(int x)
	{
		odl.resize(n + 1, LLinf);
		for(int i = 0 ; i <= n;i++)
			odl[i] = LLinf;
		odl[x] = 0;
		for(int i = 0 ;i <= n;i++)
			for(auto s : graf)
				odl[s.fi.se] = min(odl[s.fi.se], odl[s.fi.fi] + s.se);
		for(auto s : graf)
			if(odl[s.fi.se] > odl[s.fi.fi] + s.se)
				f = 1;		
	}
	
	void clear()
	{
		graf.clear();
		odl.clear();
		n = 0;
	}	
};
