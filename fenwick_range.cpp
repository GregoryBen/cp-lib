|template <typename T>
struct fenwick_range {
  int n;
  vector<T> tree[2];

  fenwick_range(int _n) : n(_n) {
    assert(n > 0);
    tree[0].resize(n);
    tree[1].resize(n);
  }

  template <typename IT>
  fenwick_range(IT begin, IT end) : n(end - begin) {
    tree[0].resize(n);
    tree[1].resize(n);
    for (int i = 0; i < n; i++) {
      update(i, i, *(begin++));
    }
  }

  void update_bit(int b, int k, T x) {
    while (k < n) {
      tree[b][k] += x;
      k |= (k + 1);
    }
  }

  void update(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n - 1);
    update_bit(0, l, x);
    update_bit(0, r + 1, -x);
    update_bit(1, l, x * (l - 1));
    update_bit(1, r + 1, -x * r);
  }

  T sum(int b, int k) {
    T res{};
    while (k >= 0) {
      res += tree[b][k];
      k = (k & (k + 1)) - 1;
    }
    return res;
  }

  T query(int k) {
    return sum(0, k) * k - sum(1, k);
  }

  T query(int l, int r) {
    assert(0 <= l && l <= r && r <= n - 1);
    return query(r) - query(l - 1);
  }
};
