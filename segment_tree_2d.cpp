template <typename T, class F = function<T(const T&, const T&)>>
struct segtree2d {
  int n, m;
  vector<vector<T>> tree;
  F func;

  template <typename U>
  segtree2d(const vector<vector<U>>& a, const F& f) : func(f) {
    n = a.size();
    assert(n > 0);
    m = a[0].size();
    assert(m > 0);
    tree.resize(2 * n);
    for (int i = 0; i < 2 * n; i++) {
      tree[i].resize(2 * m);
    }
    build(a);
  }

  template <typename U>
  void build(const vector<vector<U>>& a) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        tree[i + n][j + m] = a[i][j];
      }
    }
    for (int i = n - 1; i >= 1; i--) {
      for (int j = 0; j < m; j++) {
        tree[i][j + m] = func(tree[i << 1][j + m], tree[i << 1 | 1][j + m]);
      }
    }
    for (int i = 1; i < 2 * n; i++) {
      for (int j = m - 1; j >= 1; j--) {
        tree[i][j] = func(tree[i][j << 1], tree[i][j << 1 | 1]);
      }
    }
  }

  void update(int a, int b, const T& x) {
    assert(0 <= a && a <= n - 1 && 0 <= b && b <= m - 1);
    a += n; b += m;
    tree[a][b] += x;
    for (int j = b; j >>= 1; ) {
      tree[a][j] = func(tree[a][j << 1], tree[a][j << 1 | 1]);
    }
    for (int i = a; i >>= 1; ) {
      tree[i][b] = func(tree[i << 1][b], tree[i << 1 | 1][b]);
      for (int j = b; j >>= 1; ) {
        tree[i][j] = func(tree[i][j << 1], tree[i][j << 1 | 1]);
      }
    }
  }

  T query(int xa, int xb, int ya, int yb) {
    assert(0 <= xa && xa <= xb && xb <= n - 1 && 0 <= ya && ya <= yb && yb <= m - 1);
    T res{};
    xa += n; xb += n; ya += m; yb += m;
    int l = ya, r = yb;
    while (xa <= xb) {
      if (xa % 2 == 1) {
          ya = l, yb = r;
          while (ya <= yb) {
            if (ya % 2 == 1) res = func(res, tree[xa][ya++]);
            if (yb % 2 == 0) res = func(res, tree[xa][yb--]);
            ya /= 2; yb /= 2;
          }
          xa++;
      }
      if (xb % 2 == 0) {
        ya = l, yb = r;
        while (ya <= yb) {
          if (ya % 2 == 1) res = func(res, tree[xb][ya++]);
          if (yb % 2 == 0) res = func(res, tree[xb][yb--]);
          ya /= 2; yb /= 2;
        }
        xb--;
      }
      xa /= 2; xb /= 2;
    }
    return res;
  }
};
