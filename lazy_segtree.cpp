template <typename Q, typename L>
struct segtree {
  int n;
  pair<Q, L> id;
  vector<Q> tree;
  vector<L> delay;
  vector<bool> has;

  Q unite(const Q &a, const Q &b) const {
    Q res;
    ...
    // res.mn = min(a.mn, b.mn);
    // res.index = a.mn <= b.mn ? a.index : b.index;
    // res.cnt = (a.mn == res.mn ? a.cnt : 0) + (b.mn == res.mn ? b.cnt : 0);
    return res;
  }

  L apply_lazy(L x, L y) {
    L res;
    ...
    return res;
  }

  Q apply(L x, const Q &a) {
    Q res;
    ...
    return res;
  }

  segtree(int n_) : n(n_) {
    assert(n > 0);
    tree.resize(2 * n, id.first);
    has.resize(n);
    delay.resize(n, id.second);
  }

  template <typename IT>
  segtree(IT begin, IT end) : n(end - begin) {
    assert(n > 0);
    tree.resize(2 * n, id.first);
    has.resize(n);
    delay.resize(n, id.second);
    copy(begin, end, tree.begin() + n);
    for (int i = n - 1; i >= 1; i--) 
      tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
  }

  template <typename I>
  void set_leaves(I create) {
    for (int i = 0; i < n; i++) 
      tree[n + i] = create(i);
    for (int i = n - 1; i >= 1; i--) 
      tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
  }

  void _apply(int i, const L &x) {
    tree[i] = apply(x, tree[i]);
    if (i < n) {
      has[i] = true;
      delay[i] = apply_lazy(x, delay[i]);
    }
  }

  void _rebuild(int i) {
    for (i /= 2; i; i /= 2)
      tree[i] = apply(delay[i], unite(tree[2 * i], tree[2 * i + 1]));
  }

  void _propagate(int i) {
    for (int j = 31 - __builtin_clz(i); j > 0; j--) {
      int k = i >> j;
      if (has[k]) {
        _apply(2 * k, delay[k]);
        _apply(2 * k + 1, delay[k]);
        has[k] = false, delay[k] = id.second;
      }
    }
  }

  void replace(int i, Q v) {
    i += n;
    _propagate(i);
    tree[i] = v;
    _rebuild(i);
  }

  void update(int i, int j, L x) {
    assert(0 <= i && i <= j && j <= n - 1);
    i += n, j += n + 1;
    _propagate(i), _propagate(j - 1);
    for (int l = i, r = j; l < r; l /= 2, r /= 2) {
      if (l & 1) _apply(l++, x);
      if (r & 1) _apply(--r, x);
    }
    _rebuild(i), _rebuild(j - 1);
  }

  Q get(int i) {
    assert(i <= n - 1);
    i += n;
    _propagate(i);
    return tree[i];
  }

  Q query(int i, int j, Q x, Q y) {
    assert(0 <= i && i <= j && j <= n - 1);
    i += n, j += n + 1;
    _propagate(i), _propagate(j - 1);
    Q res_front = x, res_back = y;
    for (; i < j; i /= 2, j /= 2) {
      if (i & 1) res_front = unite(res_front, tree[i++]);
      if (j & 1) res_back = unite(tree[--j], res_back);
    }
    return unite(res_front, res_back);
  }
  
  void debug() {
    #ifdef LOCAL
      cerr << "start" << '\n';
      for (int i = 0; i < 2 * n; i++) {
//        cerr << i << ' ' << tree[i].sum << ' ' << tree[i].k << ' ';
        if (i < n) {
//          cerr << delay[i].first << ' ' << delay[i].second << '\n';
        } else {
          cerr << '\n';
        }
      }
      cerr << "end" << '\n';
    #endif // LOCAL
  }
};
