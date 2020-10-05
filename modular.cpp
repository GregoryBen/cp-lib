template <typename T>
T inverse(T a, T m) {
  assert(m > 0);
  if (m == 1) return 0;
  a %= m;
  if (a < 0) a += m;
  assert(a != 0);
  if (a == 1) return 1;
  return m - modinv(m, a) * m / a;
}

template <int MOD>
class modular {
  using value_type = int;
  static_assert(MOD > 1, "Modulus must be greater than 1");

 private:
  value_type x;

  template <typename T>
  static value_type normalize (T value) noexcept {
    if (value < 0) {
      value = (-value) % MOD;
      return (value_type) (value ? value : MOD - value);
    }
    return (value_type) (value % MOD);
  }

 public:
  modular() : x(0) {
  }

  template <typename T>
  modular(T value) : x(normalize(value)) {
  }

  modular operator + () const {
    return modular(*this);
  }

  modular operator - () const {
    if (x != 0) x = MOD - x;
    return modular(*this);
  }

  modular& operator++() {
    return ++x, *this;
  }

  modular& operator--() {
    return --x, *this;
  }

  modular operator++(int) {
    modular t = *this; return ++x, t;
  }

  modular operator--(int) {
    modular t = *this;
    return --x, t;
  }

  modular& operator += (const modular &p) {
    if ((x += p.x) >= MOD) x -= MOD;
    return (*this);
  }

  modular& operator -= (const modular &p) {
    if ((x += MOD - p.x) >= MOD) x -= MOD;
    return (*this);
  }

  modular& operator *= (const modular &p) {
    x = (int) (1LL * x * p.x % MOD);
    return (*this);
  }

  modular& operator /= (const modular &p) {
    return *this *= modular(inverse(p.x, MOD));
  }

  modular operator + (const modular &p) const {
    return (modular(*this) += p);
  }

  modular operator - (const modular &p) const {
    return (modular(*this) -= p);
  }

  modular operator * (const modular &p) const {
    return (modular(*this) *= p);
  }

  modular operator / (const modular &p) const {
    return (modular(*this) /= p);
  }

  bool operator==(const modular &p) const {
    return x == p.x;
  }

  bool operator!=(const modular &p) const {
    return x != p.x;
  }

  bool operator!() const {
    return !x;
  }

  template <typename T>
  explicit operator T() const {
    return static_cast<T>(x);
  }

  friend std::istream& operator >> (std::istream &in, modular &p) {
    long long v;
    in >> v;
    p = modular(v);
    return in;
  }

  friend std::ostream& operator << (std::ostream &out, const modular &p) {
    return out << p.x;
  }

  friend string to_string(const modular& p) {
    return to_string(p.x);
  }
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

const int md = (int) ...|;
using mint = modular<md>;
