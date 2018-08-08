
// na cfie
// MAX
// 1<<22 long double -> 500 MB
// 1<<22 double -> 330 MB
// 1<<21 long double -> 250 MB
// 1<<21 double -> 170 MB
// 1<<20 long double -> 130 MB
// 1<<20 double -> 90 MB
// 1e6 x 1e6 -> 2 s na double 3,5 s na long double
// 2e6 x 2e6 -> 4 s na double

namespace FFT {
      #define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628
	const int MAX = 1 << 20; // maksymalny rozmiar wyniku (2 * maksymalny rozmiar wejscia)

	typedef complex<double> comp; // można zmienić na long double

	int N;
	comp omega[MAX];
	comp a1[MAX], a2[MAX];
	comp z1[MAX], z2[MAX];

	void fft(comp *a, comp *z, int m = N) {
		if (m == 1) {
			z[0] = a[0];
		} else {
			int s = N/m;
			m /= 2;

			fft(a, z, m);
			fft(a+s, z+m, m);

			for(int i = 0 ;i < m;i++)
                  {
				comp c = omega[s*i] * z[m+i];
				z[m+i] = z[i] - c;
				z[i] += c;
			}
		}
	}

	void mult(LL *a, LL *b, LL *c, int len) {
		N = 2*len;
		while (N & (N-1)) ++N;
		assert(N <= MAX);

		for(int i = 0 ;i < N; i++) a1[i] = 0;
		for(int i = 0 ;i < N; i++) a2[i] = 0;
		for(int i = 0;i < len; i++)a1[i] = a[i];
		for(int i = 0;i < len; i++)a2[i] = b[i];

		for(int i = 0 ;i < N; i++) omega[i] = polar(1.0, 2*PI/N*i);
		fft(a1, z1, N);
		fft(a2, z2, N);

		for(int i = 0 ;i < N; i++) omega[i] = comp(1, 0) / omega[i];
		for(int i = 0 ;i < N; i++) a1[i] = z1[i] * z2[i] / comp(N, 0);
		fft(a1, z1, N);

		for(int i = 0;i < 2 * len; i++)c[i] = round(z1[i].real());
	}
}

const int MAX = 1<<20; // rozmiar wyniku (2 * dlugosc na wejsciu)

void mult_mod(LL *a, LL *b, LL *c, int len, int mod)
{
	static LL a0[MAX], a1[MAX];
	static LL b0[MAX], b1[MAX];
	static LL c0[MAX], c1[MAX], c2[MAX];

	for(int i = 0; i < len; i++) a0[i] = a[i] & 0xFFFF;
	for(int i = 0; i < len; i++) a1[i] = a[i] >> 16;

	for(int i = 0; i < len; i++) b0[i] = b[i] & 0xFFFF;
	for(int i = 0; i < len; i++) b1[i] = b[i] >> 16;

	FFT::mult(a0, b0, c0, len);
	FFT::mult(a1, b1, c2, len);

	for(int i = 0; i < len; i++) a0[i] += a1[i];
	for(int i = 0; i < len; i++) b0[i] += b1[i];
	FFT::mult(a0, b0, c1, len);
	for(int i = 0; i < 2 * len; i++) c1[i] -= c0[i] + c2[i];

	for(int i = 0; i < 2 * len; i++) c1[i] %= mod;
	for(int i = 0; i < 2 * len; i++) c2[i] %= mod;
	for(int i = 0; i < 2 * len; i++) c[i] = (c0[i] + (c1[i] << 16) + (c2[i] << 32)) % mod;
}
