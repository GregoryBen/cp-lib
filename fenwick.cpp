|template <typename T>
struct fenwick {
  int n;
  vector<T> tree;

  fenwick(int _n): n(_n) {
    assert(n > 0);
    tree.resize(n);
  }

  template <typename IT>
  fenwick(IT begin, IT end) : n(end - begin) {
    assert(n > 0);
    tree.resize(n);
    build(begin, end);
  }
  
  template <typename IT>
  void build(IT begin, IT end) {
    partial_sum(begin, end, tree.begin());
    for (int i = n - 1; i > 0; i--) {
      int k = (i & (i + 1)) - 1;
      if (k >= 0) tree[i] -= tree[k];
    }
  }

  void update(int k, T x) {
    while (k < n) {
      tree[k] += x;
      k |= (k + 1);
    }
  }

  T query(int k) {
    T res{};
    while (k >= 0) {
      res += tree[k];
      k = (k & (k + 1)) - 1;
    }
    return res;
  }

  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
  
  int lower_bound(T x) {
    T res{};
    int pos = -1;
    for (int i = 31 - __builtin_clz(n); i >= 0; i--) {
      int add = (1 << i) - 1;
      T cur = (pos + add == -1 ? 0 : tree[pos + add]);
      if (pos + add < n - 1 && res + cur < x) {
        res += cur;
        pos += add;
      }
    }
    return pos + 1;
  }
};
