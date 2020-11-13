|template <typename T>
struct matrix {
  int n, m;
  vector<vector<T>> val;

  matrix(int _n, int _m, T x = 0) : n(_n), m(_m) {
    assert(n > 0 && m > 0);
    val.resize(n);
    for (int i = 0; i < n; i++) {
      val[i].resize(m, x);
    }
  }

  matrix(const vector<vector<T>>& a) {
    assert(a.size() > 0 && a[0].size() > 0);
    n = a.size(); m = a[0].size();
    val.resize(n);
    for (int i = 0; i < n; i++) {
      assert((int) a[i].size() == m);
      val[i].resize(m);
      for (int j = 0; j < m; j++) {
        val[i][j] = a[i][j];
      }
    }
  }

  T& operator () (int i, int j) {
    return val[i][j];
  }

  matrix operator - () const {
    matrix res(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res.val[i][j] = -val[i][j];
      }
    }
    return res;
  }

  matrix operator + (const matrix &other) const {
    assert(n == other.n && m ==  other.m);
    matrix res(n, m);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        res.val[i][j] = val[i][j] + other.val[i][j];
      }
    }
    return res;
  }

  matrix operator - (const matrix &other) const {
    assert(n == other.n && m ==  other.m);
    matrix res(n, m);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        res.val[i][j] = val[i][j] - other.val[i][j];
      }
    }
    return res;
  }

  matrix operator * (const matrix &other) const {
    assert(m == other.n);
    int L = other.m;
    matrix res(n, L);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < L; j++) {
        for(int k = 0; k < m; k++) {
          res.val[i][j] = res.val[i][j] + val[i][k] * other.val[k][j];
        }
      }
    }
    return res;
  }

  matrix& operator += (const matrix &other){
    return *this = *this + other;
  }

  matrix& operator -= (const matrix &other){
    return *this = *this - other;
  }

  matrix& operator *= (const matrix &other){
    return *this = *this * other;
  }

  static matrix eye(int n) {
    assert(n >= 0);
    matrix I(n, n);
    for (int i = 0; i < n; i++) {
      I.val[i][i] = 1;
    }
    return I;
  }

  matrix& operator = (const matrix &other) {
    n = other.n, m = other.m;
    val.resize(n);
    for(int i = 0; i < n; i++) {
      val[i] = other.val[i];
    }
    return *this;
  }

  bool operator == (const matrix &other) const {
    if (n != other.n || m != other.m) return false;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (val[i][j] != other.val[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
};

template <typename T, typename U>
matrix<T> power(const matrix<T>& A, U k) {
  assert(k >= 0 && A.n == A.m);
  matrix<T> res = matrix<T>::eye(A.m);
  matrix<T> x = A;
  U p = k;
  while (p > 0) {
    if (p & 1) {
      res *= x;
    }
    x *= x;
    p >>= 1;
  }
  return res;
}
