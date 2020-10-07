// update : range, query : pos

struct dynamic_segtree {
  struct node {
    ...
    // long long sum = 0;
    int x, y;
    node *l = nullptr, *r = nullptr;

    node(int _x, int _y) : x(_x), y(_y) {
    }

    void apply(... /*long long*/ v) {
      ...
      // sum += v;
    }
  };

  int n;
  node* root;

  node unite(const node &a, const node &b) {
    node res;
    ...
    // res.sum = a.sum + b.sum;
    return res;
  }

  dynamic_segtree(int _n) : n(_n) {
    root = new node(0, n - 1);
  }

  template <typename T>
  void update(node *v, int l, int r, int L, int R, T x) {
    if (l > r || L < l || q_l > R) {
        return;
    }
    if (L <= l && r <= R) {
        (*v).apply(x);
        return;
    }
    int mid = (l + r) / 2;
    if (v -> l == nullptr) {
        v -> l = new node(l, mid);
    }
    if (v -> r == nullptr) {
        v -> r = new node(mid + 1, r);
    }
    update(v -> l, l, mid, L, R, x);
    update(v -> r, mid + 1, r, L, R, x);
  }

  node query(node *v, int l, int r, int pos) {
    if (!v || l > r || pos < l || r < pos) {
        return node{};
    }
    if (l == r) {
        return *v;
    }
    int mid = (l + r) / 2;
    return unite(*v, unite(query(v -> l, l, mid, pos), query(v -> r, mid + 1, r, pos)));
  }

  template <typename T>
  void update(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n - 1);
    update(root, 0, n - 1, l, r, x)
  }

  node query(int pos) {
    assert(0 <= pos && pos <= n - 1);
    return query(root, 0, n - 1, pos);
  }
};
