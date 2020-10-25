// need dsu

struct lca_tarjan : public dsu {
  using dsu::n;

  vector<int> anc;
  vector<bool> vis;
  vector<vector<int>> que;

  lca_tarjan(int _n) : dsu(_n) {
    assert(n > 0);
    anc.resize(n);
    vis.resize(n);
    que.resize(n);
  }

  void dfs(vector<vector<int>>& g, int v = 0, int p = -1) {
    anc[v] = v;
    for (int i : g[v]) {
      if (i == p) continue;
      dfs(g, i, v);
      unite(v, i);
      anc[find(v)] = v;
    }
    vis[v] = true;
    for (int i : que[v]) {
      if (vis[i]) {
        cout << "LCA " << v + 1 << " and " << i + 1 << " is " << anc[find(i)] + 1 << '\n';
      }
    }
  }

  void add(int u, int v) {
    assert(0 <= u && u <= n - 1 && 0 <= v && v <= n - 1);
    que[u].emplace_back(v);
    que[v].emplace_back(u);
  }
};
