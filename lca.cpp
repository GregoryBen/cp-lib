// O(n) preprocessing O(log n) per query

|struct LCA {
  int n;
  vector<int> height, first, euler, segtree;
  vector<bool> vis;

  LCA(vector<vector<int>>& g, int root = 0) : n(g.size()) {
    assert(n > 0);
    height.resize(n);
    first.resize(n);
    vis.resize(n);
    euler.reserve(2 * n);
    dfs(g, root);
    int m = euler.size();
    segtree.resize(4 * m);
    build(1, 0, m - 1);
  }

  void dfs(vector<vector<int>>& g, int v, int h = 0) {
    vis[v] = true;
    height[v] = h;
    first[v] = euler.size();
    euler.emplace_back(v);
    for (int i : g[v]) {
      if (vis[i]) continue;
      dfs(g, i, h + 1);
      euler.emplace_back(v);
    }
  }

  void build(int v, int l, int r) {
    if (l == r) {
      segtree[v] = euler[l];
      return;
    }
    int m = (l + r) >> 1;
    build(2 * v, l, m);
    build(2 * v + 1, m + 1, r);
    int x = segtree[2 * v];
    int y = segtree[2 * v + 1];
    segtree[v] = (height[x] < height[y] ? x : y);
  }

  int query(int v, int l, int r, int L, int R) {
    if (L > r || l > R) {
      return -1;
    }
    if (L <= l && r <= R) {
      return segtree[v];
    }
    int m = (l + r) >> 1;
    int x = query(2 * v, l, m, L, R);
    int y = query(2 * v + 1, m + 1, r, L, R);
    if (x == -1) {
      return y;
    }
    if (y == -1) {
      return x;
    }
    return (height[x] < height[y] ? x : y);
  }

  int solve(int l, int r) {
    assert(0 <= l && l <= n - 1 && 0 <= r && r <= n - 1);
    int x = first[l];
    int y = first[r];
    if (x > y) {
      swap(x, y);
    }
    return query(1, 0, euler.size() - 1, x, y);
  }
};
