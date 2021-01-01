// https://old.yosupo.jp/submission/34558 (1000000007)
// https://old.yosupo.jp/submission/34559 (998244353)

constexpr long double PI = acos(-1.0L);

template <typename T>
struct comp {
  T x, y;
  comp() { x = y = 0; }
  comp(T _x, T _y) : x(_x), y(_y) {}

  friend comp<T> operator+(comp<T> a, comp<T> b) { return comp(a.x + b.x, a.y + b.y); }
  friend comp<T> operator-(comp<T> a, comp<T> b) { return comp(a.x - b.x, a.y - b.y); }
  friend comp<T> operator*(comp<T> a, comp<T> b) { return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
  friend comp<T> operator/(comp<T> a, T b) { return comp(a.x / b, a.y / b); }
  friend comp<T> conj(comp<T> a) { return comp(a.x, -a.y); }
};

void fft(vector<comp<double>> &a) {
  int n = a.size();
  int L = 31 - __builtin_clz(n);
  static vector<comp<double>> root(2, {1, 0});
  static vector<comp<long double>> R(2, {1, 0});
  for (int k = 2; k < n; k <<= 1) {
    R.resize(n);
    root.resize(n);
    comp<long double> x(cos(PI / k), sin(PI / k));
    for (int i = k; i < 2 * k; i++) {
      R[i] = (i & 1 ? R[i / 2] * x : R[i / 2]);
      root[i] = {(double) R[i].x, (double) R[i].y};
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
        comp<double> z = root[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
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
  vector<comp<double>> in(n);
  vector<comp<double>> out(n);
  for (int i = 0; i < (int) a.size(); i++) {
    in[i].x = a[i];
  }
  for (int i = 0; i < (int) b.size(); i++) {
    in[i].y = b[i];
  }
  fft(in);
  for (comp<double> &x : in) {
    x = x * x;
  }
  for (int i = 0; i < n; i++) {
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  }
  fft(out);
  for (int i = 0; i < (int) res.size(); i++) {
    res[i] = llround(out[i].y / (4 * n));
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
  vector<comp<double>> L(n);
  vector<comp<double>> R(n);
  vector<comp<double>> outs(n);
  vector<comp<double>> outl(n);
  for (int i = 0; i < (int) a.size(); i++) {
    L[i] = comp<double> ((int) a[i] / cut, (int) a[i] % cut);
  }
  for (int i = 0; i < (int) b.size(); i++) {
    R[i] = comp<double> ((int) b[i] / cut, (int) b[i] % cut);
  }
  fft(L);
  fft(R);
  for (int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = {outs[j].y, -outs[j].x};
  }
  fft(outl);
  fft(outs);
  for (int i = 0; i < (int) res.size(); i++) {
    long long av = (long long) (outl[i].x + 0.5);
    long long bv = (long long) (outl[i].y + 0.5) + (long long) (outs[i].x + 0.5);
    long long cv = (long long) (outs[i].y + 0.5);
    res[i] = ((av % m * cut + bv) % m * cut + cv) % m;
  }
  return res;
}
