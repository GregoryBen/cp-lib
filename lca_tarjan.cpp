// incomplete!

struct lca_tarjan {
  int n;
  vector<int> anc, vis, anc;
  vector<bool> vis;
  vector<vector<int>> que;
  dsu d;

  lca_tarjan(vector<vector<int>>& g) : n(g.size()) {
    assert(n > 0);
    anc.resize(n);
    vis.resize(n);
    d.resize(n);
    dfs(g, 0);
  }

  void dfs(vector<vector<int>>& g, int v) {
    vis[v] = true;
    anc[v] = v;
    for (int i : g[v]) {
      if (vis[i]) continue;
      dfs(i);
      dsu
    }
  }

  void add(int u, int v) {
    que[u].emplace_back(v);
    que[v].emplace_back(u);
  }
};
