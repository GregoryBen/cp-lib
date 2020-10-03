|struct persistent_segtree {
  static const int N = (int) 1e7;
  struct node {
    ...
    // long long sum = 0;
    // int k = 1;
    // long long lazy = 0;

    void apply(long long x) {
      ...
      // sum = x * k;
      // lazy += x;
    }
  };

  int n;
  int pos = 0;
  int l[N], r[N];
  node tree[N];
  vector<int> form;

  int copy(int cur) {
    tree[pos] = tree[cur];
    l[pos] = l[cur];
    r[pos] = r[cur];
    return pos++;
  }

  node unite(const node &a, const node &b) const {
    node res;
    ...
    // res.sum = a.sum + b.sum;
    // res.k = a.k + b.k;
    return res;
  }

  inline void pull(int x) {
    tree[x] = unite(tree[l[x]], tree[r[x]]);
  }

  inline void push(int cur, int L, int R) {
    if (!tree[cur].lazy) return;
    if (L != R) {
      tree[l[cur] = copy(l[cur])].apply(tree[cur].lazy);
      tree[r[cur] = copy(r[cur])].apply(tree[cur].lazy);
    }
    tree[cur].lazy = 0;
  }

  template <typename T>
  int build(const vector<T>& a, int L, int R) {
    int cur = pos++;
    if (L == R) {
      tree[cur].apply(a[L]);
      return cur;
    }
    int M = (L + R) / 2;
    l[cur] = build(a, L, M);
    r[cur] = build(a, M + 1, R);
    pull(cur);
    return cur;
  }

  template <typename T>
  int update(int cur, int lo, int hi, T v, int L, int R) {
    if (R < lo || hi < L) return cur;
    int x = copy(cur);
    if (lo <= L && R <= hi) {
      tree[x].apply(v);
      return x;
    }
    push(x, L, R);
    int M = (L + R) / 2;
    l[x] = update(l[x], lo, hi, v, L, M);
    r[x] = update(r[x], lo, hi, v, M + 1, R);
    pull(x);
    return x;
  }

  node query(int cur, int lo, int hi, int L, int R) {
    if (lo <= L && R <= hi) return tree[cur];
    if (R < lo || hi < L) return node{};
    push(cur, L, R);
    int M = (L + R) / 2;
    return unite(query(l[cur], lo, hi, L, M), query(r[cur], lo, hi, M + 1, R));
  }

  template <typename T>
  void build(const vector<T>& a) {
    n = (int) a.size();
    assert(n > 0);
    form.push_back(build(a, 0, n - 1));
  }

  void complete(int k) {
    assert(!form.empty() && 0 <= k && k < (int) form.size());
    form.push_back(form[k]);
  }

  template <typename T>
  void update(int lo, int hi, T v) {
    assert(0 <= lo &&  lo <= hi && hi <= n - 1);
    form.push_back(update(form.back(), lo, hi, v, 0, n - 1));
  }

  node query(int ver, int lo, int hi) {
    assert(!form.empty() && ver < (int) form.size() && 0 <= lo && lo <= hi && hi <= n - 1);
    return query(form[ver], lo, hi, 0, n - 1);
  }
};

persistent_segtree pseg;
