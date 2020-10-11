// update : range, query : pos

template <typename B>
struct dynamic_segtree {
  struct node {
   ...
//     long long sum = 0;
    node *l = nullptr, *r = nullptr;

    void apply(... /*long long*/ v, B L, B R) {
     ...
//       sum += v;
    }
  };

  B n;
  node* root;

  node unite(const node &a, const node &b) {
    node res;
   ...
//     res.sum = a.sum + b.sum;
    return res;
  }

  dynamic_segtree(B _n) : n(_n) {
    assert(n > 0);
    root = new node();
  }

  template <typename IT>
  dynamic_segtree(IT begin, IT end) : n(end - begin) {
    assert(n > 0);
    root = new node();
    for (int i = 0; i < n; i++) {
      update(i, i, *(begin++));
    }
  }

  template <typename T>
  void update(node *v, B l, B r, B L, B R, T x) {
    if (R < l || L > r) {
        return;
    }
    if (L <= l && r <= R) {
        (*v).apply(x, l, r);
        return;
    }
    B mid = l + (r - l) / 2;
    if (v->l == nullptr) {
        v->l = new node();
    }
    if (v->r == nullptr) {
        v->r = new node();
    }
    update(v->l, l, mid, L, R, x);
    update(v->r, mid + 1, r, L, R, x);
  }

  node query(node *v, B l, B r, B pos) {
    if (!v || pos < l || r < pos) {
        return node{};
    }
    if (l == r) {
        return *v;
    }
    B mid = l + (r - l) / 2;
    return unite(*v, unite(query(v->l, l, mid, pos), query(v->r, mid + 1, r, pos)));
  }

  template <typename T>
  void update(B l, B r, T x) {
    assert(0 <= l && l <= r && r <= n - 1);
    update(root, 0, n - 1, l, r, x);
  }

  node query(B pos) {
    assert(0 <= pos && pos <= n - 1);
    return query(root, 0, n - 1, pos);
  }
};
