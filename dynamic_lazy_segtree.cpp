// under construction!

template <typename B = int>
struct dynamic_segtree {
  struct node {
//    ...
    long long sum = 0;
    long long lazy = 0;
    node *l = nullptr, *r = nullptr;

    node() { }

    void apply(long long /*long long*/ x, int l, int r) {
//      ...
      sum += x * (r - l + 1);
      lazy += x;
    }
  };

  B n;
  node* root;

  node unite(const node &a, const node &b) {
    node res;
//    ...
    res.sum = a.sum + b.sum;
    res.k = a.k + b.k;
    return res;
  }

  inline void pull(node* v) {
    *v = unite(v->l, v->r);
  }

  inline void push(node* v, B l, B r) {
    B mid = left + (right - begin) / 2;
    if (l == nullptr) {
      l = new dynamic_segtree(left, mid);
      r = new dynamic_segtree(mid + 1, right);
    }
    if (lazy != id.first) {
      l->apply(lazy, l, mid);
      r->apply(lazy, mid + 1, r);
      lazy = 0;
    }
  }

  dynamic_segtree(B _n) : n(_n) {
    assert(n > 0);
    root = new node(0, n - 1);
  }

  template <typename It>
  dynamic_segtree(IT begin, IT end) : n(end - begin) {
    assert(n > 0);
    root = new node(0, n - 1);
    build(root, begin, end, 0, n - 1);
  }

  template <typename IT>
  void build(node* v, IT begin, IT end, B l, B r) {
    assert(begin + l <= end);
    if (l == r) {
      (*v).apply(*(begin + l), l, r);
      return;
    }
    B mid = l + (r - l) / 2;
    v->l = new dynamic_segtree();
    v->r = new dynamic_segtree();
    build(v->l, begin, end, l, mid);
    build(v->r, begin, end, mid + 1, r);
    pull(v);
  }

  template <typename T>
  void update(node* v, B l, B r, B L, B R, T x) {
    if (r < L || R < l || x = id.first) {
      return;
    }
    if (L <= l && r <= R) {
      (*v).apply(x, l, r);
      return;
    }
    push();
    l->update(l, r, x);
    r->update(l, r, x);
    B m = l + (r - l) / 2;
    tree = unite(l->tree, r->tree);
  }

  node query(node* v, B l, B r, B L, B R) {
    if (!v ||r < left || right < l) return node{};
    if (l <= left && right <= r) return *v;
    push();
    B mid = left + (right - left) / 2;
    return unite(query(v->l, mid, L, R), query(v->r, mid + 1, r, L, R));
  }
};

