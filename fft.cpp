// https://old.yosupo.jp/submission/34405 default
// https://old.yosupo.jp/submission/34411 (a bit faster in mod 1e9 + 7, slower in mod 998244353)

const long double PI = acos(-1.0L);

void fft(vector<complex<double>> &a) {
  int n = a.size();
  int L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<complex<double>> rt(2, 1);
  for (int k = 2; k < n; k <<= 1) {
    R.resize(n);
    rt.resize(n);
    complex<long double> x(cos(PI / k), sin(PI / k));
    for (int i = k; i < 2 * k; i++) {
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++) {
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    if (i < rev[i]) {
      swap(a[i], a[rev[i]]);
    }
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += k * 2) {
      for (int j = 0; j < k ; j++) {
        auto x = (double*) &rt[j + k], y = (double*) &a[i + j + k];
        complex<double> z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  if (a.empty() || b.empty()) {
    return vector<int>();
  }
  vector<int> res(a.size() + b.size() - 1);
  int L = 32 - __builtin_clz(res.size());
  int n = 1 << L;
  vector<complex<double>> in(n);
  vector<complex<double>> out(n);
  copy(a.begin(), a.end(), in.begin());
  for (int i = 0; i < (int) b.size(); i++) {
    in[i].imag(b[i]);
  }
  fft(in);
  for (complex<double> &x : in) {
    x *= x;
  }
  for (int i = 0; i < n; i++) {
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  }
  fft(out);
  for (int i = 0; i < (int) res.size(); i++) {
    res[i] = imag(out[i]) / (4 * n);
  }
  return res;
}

vector<int> multiply_mod(const vector<int> &a, const vector<int> &b, int m) {
  if (a.empty() || b.empty()) {
    return vector<int>();
  }
  vector<int> res(a.size() + b.size() - 1);
  int B = 32 - __builtin_clz(res.size());
  int n = 1 << B;
  int cut = (int) sqrt(m);
  vector<complex<double>> L(n);
  vector<complex<double>> R(n);
  vector<complex<double>> outs(n);
  vector<complex<double>> outl(n);
  for (int i = 0; i < (int) a.size(); i++) {
    L[i] = complex<double> ((int) a[i] / cut, (int) a[i] % cut);
  }
  for (int i = 0; i < (int) b.size(); i++) {
    R[i] = complex<double> ((int) b[i] / cut, (int) b[i] % cut);
  }
  fft(L);
  fft(R);
  for (int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
  }
  fft(outl);
  fft(outs);
  for (int i = 0; i < (int) res.size(); i++) {
    long long av = (long long) (real(outl[i]) + 0.5);
    long long bv = (long long) (imag(outl[i]) + 0.5) + (long long) (real(outs[i]) + 0.5);
    long long cv = (long long) (imag(outs[i]) + 0.5);
    res[i] = ((av % m * cut + bv) % m * cut + cv) % m;
  }
  return res;
}
