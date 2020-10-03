|template <typename T, class F = function<T(const T&, const T&)>>
struct Csegtree {
  int n;
  vector<T> tree;
  F func;

  template <typename IT>
  Csegtree(IT begin, IT end, const F& f) : n(end - begin), func(f) {
    tree.resize(2 * n);
    copy(begin, end, tree.begin() + n);
    for (int i = n - 1; i >= 1; i--) {
      tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  void update(int k, const T& x) {
    assert(0 <= k && k <= n - 1);
    k += n;
    tree[k] += x;
    for (k /= 2; k >= 1; k /= 2) {
      tree[k] = func(tree[k << 1], tree[k << 1 | 1]);
    }
  }

  T query(int l, int r, const T& x, const T& y) {
    assert(0 <= l && l <= r && r <= n - 1);
    l += n; r += n;
    T res_front = x, res_back = y;
    while (l <= r) {
      if (l % 2 == 1) res_front = func(res_front, tree[l++]);
      if (r % 2 == 0) res_back = func(tree[r--], res_back);
      l /= 2; r /= 2;
    }
    return func(res_front, res_back);
  }

  T query(int l, int r, const T& x) {
    return query(l, r, x, x);
  }
};
