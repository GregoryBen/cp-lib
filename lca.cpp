// O(n) preprocessing O(log n) per query
// incomplete

|struct LCA {
  int n;
  vector<int> height, first, euler, segtree;
  vector<bool> vis;

  LCA(vector<vector<int>>& g, int root = 0) : n(g.size()) {
    height.resize(n);
    first.resize(n);
    euler.resize(2 * n);
    segtree.resize(8 * n);
    vis.resize(n);
    dfs(g, root);
    build(1, 0, m - 1); // ??
  }

  void dfs(vector<vector<int>>& g, int v, int h = 0) {
    vis[v] = true;
    height[v] = h;
    first[node] = euler.size();
    euler.emplace_back(v);
    for (int i : g[v]) {
      if (vis[i]) continue;
      dfs(g, i, h + 1);
      euler.emplace_back(v);
    }
  }

  void build(int v, int b, int e) {

  }
};
