typedef unsigned int uint;
typedef vector<int>::iterator iter;

// Indices start from 0
struct BitmapRank {
  const int bits = sizeof(int)*8;
  vector<int> vec;
  vector<int> count;

  BitmapRank() {}

  void resize(int n) {
    vec.resize((n+bits-1)/bits);
    count.resize(vec.size());
  }

  void set(int i, bool b) {
    set_bit(vec[i/bits], i %bits, b);
  }

  void build_rank() {
    for (int i = 1; i < (int)vec.size(); ++i)
      count[i] = count[i-1] + popcnt(vec[i-1]);
  }

  int rank1(int i) const {
    return i < 0 ? 0 : count[i/bits] + popcnt(vec[i/bits] << (bits - i%bits - 1));
  }

  int rank1(int i, int j) const {
    return rank1(j) - rank1(i-1);
  }

  int rank0(int i) const {
    return i < 0 ? 0 : i - rank1(i) + 1;
  }

  int rank0(int i, int j) const {
    return rank0(j) - rank0(i-1);
  }
};

//Wavelet tree with succinct representation of bitmaps
struct WaveTreeSucc {
  vector<vector<int> > C; int s;

  // sigma = size of the alphabet, ie., one more than the maximum element
  // in S.
  WaveTreeSucc(vector<int> &A, int sigma) : C(sigma*2), s(sigma) {
    build(A.begin(), A.end(), 0, s-1, 1);
  }

  void build(iter b, iter e, int L, int U, int u) {
    if (L == U)
      return;
    int M = (L+U)/2;

    // C[u][i] contains number of zeros until position i-1: [0,i)
    C[u].reserve(e-b+1); C[u].push_back(0);
    for (iter it = b; it != e; ++it)
      C[u].push_back(C[u].back() + (*it<=M));

    iter p = stable_partition(b, e, [=](int i){return i<=M;});

    build(b, p, L, M, u*2);
    build(p, e, M+1, U, u*2+1);
  }

  // Count occurrences of number c until position i.
  // ie, occurrences of c in positions [i,j]
  int rank(int c, int i) const {
    // Internally we consider an interval open on the left: [0, i)
    i++;
    int L = 0, U = s-1, u = 1, M, r;
    while (L != U) {
      M = (L+U)/2;
      r = C[u][i]; u*=2;
      if (c <= M)
        i = r, U = M;
      else
        i -= r, L = M+1, ++u;
    }
    return i;
  }

  // Find the k-th smallest element in positions [i,j].
  // The smallest element is k=1
  int quantile(int k, int i, int j) const {
    // internally we we consider an interval open on the left:  [i, j)
    j++;
    int L = 0, U = s-1, u = 1, M, ri, rj;
    while (L != U) {
      M = (L+U)/2;
      ri = C[u][i]; rj = C[u][j]; u*=2;
      if (k <= rj-ri)
        i = ri, j = rj, U = M;
      else
        k -= rj-ri, i -= ri, j -= rj,
          L = M+1, ++u;
    }
    return U;
  }

  // Count number of occurrences of numbers in the range [a, b]
  // present in the sequence in positions [i, j], ie, if representing a grid it
  // counts number of points in the specified rectangle.
  mutable int L, U;
  int range(int i, int j, int a, int b) const {
    if (b < a or j < i)
      return 0;
    L = a; U = b;
    return range(i, j+1, 0, s-1, 1);
  }

  int range(int i, int j, int a, int b, int u) const {
    if (b < L or U < a)
      return 0;
    if (L <= a and b <= U)
      return j-i;
    int M = (a+b)/2, ri = C[u][i], rj = C[u][j];
    return range(ri, rj, a, M, u*2) +
      range(i-ri, j-rj, M+1, b, u*2+1);
  }
};


// Wavelet Matrix with succinct representation of bitmaps
struct WaveMatrixSucc {
  uint height;
  vector<BitmapRank> B;
  vector<int> z;

  WaveMatrixSucc(vector<int> &A) :
    WaveMatrixSucc(A, *max_element(A.begin(), A.end()) + 1) {}

  // sigma = size of the alphabet, ie., one more than the maximum element
  // in A.
  WaveMatrixSucc(vector<int> &A, int sigma)
    : height(log2(sigma - 1)),
      B(height), z(height) {
    for (uint l = 0; l < height; ++l) {
      B[l].resize(A.size());
      for (uint i = 0; i < A.size(); ++i)
        B[l].set(i, get_bit(A[i], height - l - 1));
      B[l].build_rank();

      auto it = stable_partition(A.begin(), A.end(), [=] (int c) {
          return not get_bit(c, height - l - 1);
        });
      z[l] = distance(A.begin(), it);
    }
  }

  // Count occurrences of number c until position i.
  // ie, occurrences of c in positions [i,j]
  int rank(int c, int i) const {
    int p = -1;
    for (uint l = 0; l < height; ++l) {
      if (get_bit(c, height - l - 1)) {
        p = z[l] + B[l].rank1(p) - 1;
        i = z[l] + B[l].rank1(i) - 1;
      } else {
        p = B[l].rank0(p) - 1;
        i = B[l].rank0(i) - 1;
      }
    }
    return i - p;
  }

  // Find the k-th smallest element in positions [i,j].
  // The smallest element is k=1
  int quantile(int k, int i, int j) const {
    int element = 0;
    for (uint l = 0; l < height; ++l) {
      int r = B[l].rank0(i, j);
      if (r >= k) {
        i = B[l].rank0(i-1);
        j = B[l].rank0(j) - 1;
      } else {
        i = z[l] + B[l].rank1(i-1);
        j = z[l] + B[l].rank1(j) - 1;
        k -= r;
        set_bit(element, height - l - 1, 1);
      }
    }
    return element;
  }

  // Count number of occurrences of numbers in the range [a, b]
  // present in the sequence in positions [i, j], ie, if representing a grid it
  // counts number of points in the specified rectangle.
  int range(int i, int j, int a, int b) const {
    return range(i, j, a, b, 0, (1 << height)-1, 0);
  }

  int range(int i, int j, int a, int b, int L, int U, int l) const {
    if (b < L || U < a)
      return 0;

    int M = L + (U-L)/2;
    if (a <= L && U <= b)
      return j - i + 1;
    else {
      int left = range(B[l].rank0(i-1), B[l].rank0(j) - 1,
                       a, b, L, M, l + 1);
      int right = range(z[l] + B[l].rank1(i-1), z[l] + B[l].rank1(j) - 1,
                        a, b, M+1, U, l+1);
      return left + right;
    }
  }
};
