template <typename T>
T modinv(T a, T m) {
  assert(m > 0);
  if (m == 1) return 0;
  a %= m;
  if (a < 0) a += m;
  assert(a != 0);
  if (a == 1) return 1;
  return m - modinv(m, a) * m / a;
}

template <int MOD>
struct modular {
  static_assert(MOD > 0);
  int r;
  modular() { r = 0; }
  modular(long long _r) : r(int(_r)) { if (abs(r) >= MOD) r %= MOD; if(r < 0) r += MOD; }
  modular inv() const { modular res; res.r = modinv(int(*this), MOD); return res; }

  modular operator -() const { return modular(-r); }

  modular operator + (const modular &t) const { return modular(*this) += t; }
  modular operator - (const modular &t) const { return modular(*this) -= t; }
  modular operator * (const modular &t) const { return (r * t.r) % MOD; }
  modular operator / (const modular &t) const { return *this * t.inv(); }

  modular operator += (const modular &t) { r += t.r; if(r >= MOD) r -= MOD; return *this; }
  modular operator -= (const modular &t) { r -= t.r; if(r < 0) r += MOD; return *this; }
  modular operator *= (const modular &t) { return *this = *this * t; }
  modular operator /= (const modular &t) { return *this = *this / t; }

  bool operator==(const modular &t) const { return r == t.r; }
  bool operator!=(const modular &t) const { return r != t.r; }

  explicit operator int() const { return r; }
};

template <typename T, typename U>
T power(T a, U b) {
  assert(b >= 0);
  T res = 1;
  while (b > 0) {
    if (b & 1) {
      res = res * a;
    }
    a *= a; b >>= 1;
  }
  return res;
}

template <int T>
istream& operator >> (istream &in, modular<T>& x) {
  long long _r;
  in >> _r;
  x = modular<T>(_r);
  return in;
}

template <int T>
ostream& operator << (ostream &out, modular<T>& x) {
  return out << int(x);
}

template <int T>
string to_string(const modular<T>& x) {
  return to_string(int(x));
}

const int md = (int) ...|;
using mint = modular<md>;
