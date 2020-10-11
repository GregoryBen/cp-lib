template <typename B>
struct dynamic_segtree {
  struct node {
    ...
//    long long sum = 0;
//    long long lazy = 0;
    node *l = nullptr, *r = nullptr;

    void apply(... /*long long*/ x, B L, B R) {
      ...
//      sum += x * (R - L + 1);
//      lazy += x;
    }
  };

  B n;
  node* root;

  node unite(const node &a, const node &b) {
    node res;
    ...
//    res.sum = a.sum + b.sum;
    return res;
  }

  inline void pull(node* v) {
    node cur = unite(*(v->l), *(v->r));
    cur.l = v->l;
    cur.r = v->r;
    *v = cur;
  }

  inline void push(node* v, B L, B R) {
    B M = L + (R - L) / 2;
    if (v->l == nullptr) {
      v->l = new node();
      v->r = new node();
    }
    if (L != R) {
      (*(v->l)).apply(v->lazy, L, M);
      (*(v->r)).apply(v->lazy, M + 1, R);
      v->lazy = 0;
    }
  }

  dynamic_segtree(B _n) : n(_n) {
    assert(n > 0);
    root = new node();
  }

  template <typename IT>
  dynamic_segtree(IT begin, IT end) : n(end - begin) {
    assert(n > 0);
    root = new node();
    build(root, begin, end, 0, n - 1);
  }

  template <typename IT>
  void build(node* v, IT begin, IT end, B L, B R) {
    assert(begin + L < end);
    if (L == R) {
      (*v).apply(*(begin + L), L, R);
      return;
    }
    B M = L + (R - L) / 2;
    v->l = new node();
    v->r = new node();
    build(v->l, begin, end, L, M);
    build(v->r, begin, end, M + 1, R);
    pull(v);
  }

  template <typename T>
  void update(node* v, B l, B r, B L, B R, T x) {
    if (r < L || R < l) {
      return;
    }
    if (l <= L && R <= r) {
      (*v).apply(x, L, R);
      return;
    }
    push(v, L, R);
    B M = L + (R - L) / 2;
    update(v->l, l, r, L, M, x);
    update(v->r, l, r, M + 1, R, x);
    pull(v);
  }

  node query(node* v, B l, B r, B L, B R) {
    if (!v || R < l || r < L) return node{};
    if (l <= L && R <= r) return *v;
    push(v, L, R);
    B M = L + (R - L) / 2;
    return unite(query(v->l, l, r, L, M), query(v->r, l, r, M + 1, R));
  }

  template <typename T>
  void update(B l, B r, T x) {
    assert(0 <= l && l <= r && r <= n - 1);
    update(root, l, r, 0, n - 1, x);
  }

  node query(B l, B r) {
    assert(0 <= l && l <= r && r <= n - 1);
    return query(root, l, r, 0, n - 1);
  }
};
