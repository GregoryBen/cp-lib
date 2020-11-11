|struct mod_matrix {
  int n, m;
  vector<vector<mint>> val;

  mod_matrix(int _n, int _m) : n(_n), m(_m) {
    assert(n > 0 && m > 0);
    val.resize(n);
    for (int i = 0; i < n; i++) {
      val[i].resize(m);
    }
  }

  template <typename T>
  mod_matrix(const vector<vector<T>>& a) {
    assert(a.size() > 0 && a[0].size() > 0);
    n = a.size(); m = a[0].size();
    for (int i = 0; i < n; i++) {
      assert(a[i].size() == m);
      for (int j = 0; j < m; j++) {
        val[i][j] = a[i][j];
      }
    }
  }

  mint& operator () (int i, int j) {
    return val[i][j];
  }

  mod_matrix operator - () const {
    mod_matrix A(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        A.val[i][j] = -val[i][j];
      }
    }
    return A;
  }

  mod_matrix& operator += (const mod_matrix& A) {
    assert(n == A.n && m == A.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        val[i][j] += A.val[i][j];
      }
    }
    return *this;
  }

  mod_matrix& operator -= (const mod_matrix& A) {
    assert(n == A.n && m == A.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        val[i][j] -= A.val[i][j];
      }
    }
    return *this;
  }

  mod_matrix& operator *= (const mod_matrix& A) {
    assert(m == A.n);
    for (int i = 0; i < n; i++) {
      vector<mint> row(A.m);
      for (int j = 0; j < A.m; j++) {
        for (int k = 0; k < A.n; k++) {
          row[j] += val[i][k] * A.val[k][j];
        }
      }
      val[i] = row;
    }
    return *this;
  }

  static mod_matrix eye(int n) {
    assert(n >= 0);
    mod_matrix I(n, n);
    for (int i = 0; i < n; i++) {
      I.val[i][i] = 1;
    }
    return I;
  }

  // mod should be prime, matrix invertible
  mod_matrix inv() const {
    assert(n == m);
    mod_matrix B = eye(m);
    vector<vector<mint>>  a = val;
    vector<vector<mint>>& b = B.val;
    for (int i = 0, j, k; i < m; i++) {
      for (j = i; j < m && a[j][i] == 0; j++) continue;
      if (j == m) {
        return mod_matrix(0, 0);
      }
      swap(a[i], a[j]);
      swap(b[i], b[j]);
      mint inv = a[i][i].inv();
      for (k = i; k < m; k++) {
        a[i][k] *= inv;
      }
      for (k = 0; k < m; k++) {
        b[i][k] *= inv;
      }
      for (j = 0; j < m; j++) {
        if (i == j || a[j][i] == 0) continue;
        mint c = a[j][i];
        for (k = i; k < m; k++) {
          a[j][k] -= c * a[i][k];
        }
        for (k = 0; k < m; k++) {
          b[j][k] -= c * b[i][k];
        }
      }
    }
    return B;
  }

  // It can be used for any composite modulo.
  mint det() const {
    assert(n == m);
    vector<vector<mint>> a = val;
    mint D(1);
    for (int j = 0; j < m; j++) {
      for (int i = j+1; i < m; i++) {
        while (a[i][j]) {
          D = -D;
          mint t((long long) a[j][j] / (long long) a[i][j]);
          for (int k = j; k < m; k++) {
            swap(a[i][k], a[j][k] -= t * a[i][k]);
          }
        }
      }
      D *= a[j][j];
    }
    return D;
  }
};

mod_matrix operator + (mod_matrix& A, mod_matrix& B) {
  return A += B;
}

mod_matrix operator - (mod_matrix& A, mod_matrix& B) {
  return A -= B;
}

mod_matrix operator * (mod_matrix& A, mod_matrix& B) {
  return A *= B;
}

template <typename T>
mod_matrix power(const mod_matrix& A, T k) {
  assert(k >= 0 && A.n == A.m);
  mod_matrix res = mod_matrix::eye(A.m);
  mod_matrix x = A;
  T p = k;
  while (p > 0) {
    if (p & 1) {
      res *= x;
    }
    x *= x;
    p >>= 1;
  }
  return res;
}

mint dot(const mod_matrix& A, const mod_matrix& B) {
  assert(A.n == B.n && A.m == B.m);
  mint val;
  for (int i = 0; i < A.n; i++) {
    for (int j = 0; j < A.m; j++) {
      val += A.val[i][j] * B.val[i][j];
    }
  }
  return val;
}

vector<mint> operator * (const mod_matrix& A, const vector<mint>& x) {
  assert(A.m == (int) x.size());
  vector<mint> y(A.n);
  for (int i = 0; i < A.n; i++) {
    for (int j = 0; j < A.m; j++) {
      y[i] += A.val[i][j] * x[j];
    }
  }
  return y;
}

mint dot(const vector<mint>& a, const vector<mint>& b) {
  assert(a.size() == b.size());
  mint val;
  for (int i = 0; i < (int) a.size(); i++) {
    val += a[i] * b[i];
  }
  return val;
}

using matrix = mod_matrix;
