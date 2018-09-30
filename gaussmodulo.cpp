
// MOD to modulo
// w x znjduja sie rozwiazania

const int MOD = 13;

int powmod(int a, int n){
    if(n == 0) return 1;
    if(n % 2) return (a * powmod(a,n-1)) % MOD;
    int c = powmod(a, n/2);
    return (c*c) % MOD;
}
int inv(int a){
    return powmod(a, MOD-2);
}

int solve(vector<vector<int> > A, vector<int> b, vector<int>& x){
    int n = A.size();
    int m = x.size();
    if(n) assert(A[0].size() == m);
    int use = 0;
    vector<int> var;
    for(int j = 0; j < m; j++){

        int z = -1;
        for(int i = use; i < n; i++){
            if(A[i][j] % MOD != 0) z = i;
        }
        if(z == -1) continue;

        var.push_back(j);
        swap(A[z], A[use]);
        swap(b[z], b[use]);
        int inverse = inv(A[use][j]);
        b[use] = (b[use] * inverse) % MOD;
        for(int k = 0; k < m; k++){
            A[use][k] = (A[use][k] * inverse) % MOD;
        }

        for(int i = use + 1; i < n; i++){
            int mult = A[i][j];
            for(int k = 0; k < m; k++){
                A[i][k] -= mult * A[use][k];
                A[i][k] %= MOD;
                while(A[i][k] < 0) A[i][k] += MOD;
            }
            b[i] -= mult * b[use];
            b[i] %= MOD;
            while(b[i] < 0) b[i] += MOD;
        }
        use++;
    }

    for(int j = 0; j < m; j++){
        x[j] = 0;
    }
    for(int i = use-1; i >= 0; i--){
        x[var[i]] = b[i];
        for(int j = var[i] + 1; j < m; j++){
            x[var[i]] -= x[j] * A[var[i]][j];
            x[var[i]] %= MOD;
            while(x[var[i]] < 0) x[var[i]] += MOD;
        }
    }
    return use;
}
