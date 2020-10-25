struct lca_tarjan {
  int n;
  vector<int> anc, link;
  vector<bool> vis;
  vector<vector<int>> que;

  lca_tarjan(int _n) : n(_n) {
    assert(n > 0);
    anc.resize(n);
    link.resize(n);
    vis.resize(n);
    que.resize(n);
  }

  inline int find(int x) {
    return (x == link[x] ? x : (link[x] = find(link[x])));
  }

  inline void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      link[a] = b;
    }
  }

  void dfs(vector<vector<int>>& g, int v = 0) {
    vis[v] = true;
    anc[v] = v;
    for (int i : g[v]) {
      if (vis[i]) continue;
      dfs(g, i);
      unite(v, i);
      anc[find(v)] = v;
    }
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
