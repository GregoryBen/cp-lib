|template <typename T>
struct fenwick2d {
  int n, m;
  vector<vector<T>> tree;

  fenwick2d(int _n, int _m) : n(_n), m(_m) {
    tree.resize(n);
    for (int i = 0; i < n; i++) {
      tree[i].resize(m);
    }
  }

  void add(int x, int y, T delta) {
    for (int i = x; i < n; i = i | (i + 1)) {
      for (int j = y; j < m; j = j | (j + 1)) {
        tree[i][j] += delta;
      }
    }
  }

  T query(int x, int y) {
    T ret{};
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        ret += tree[i][j];
      }
    }
    return ret;
  }

  T query(int xl, int xr, int yl, int yr) {
    return query(xr, yr) - query(xl - 1, yr) - query(xr, yl - 1) + query(xl - 1, yl - 1);
  }
};
