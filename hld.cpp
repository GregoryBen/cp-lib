// incomplete

template <typename T>
struct HeavyLight {
  int n;
  bool edge_val;
  vector<int> par;
  vector<int> heavy;
  vector<int> sz;
  vector<int> depth;
  vector<int> root;
  vector<int> pos;

  template <typename G>
  void dfs(const vector<vector<int>>& g, int v) {
    int sz[v] = 1;
    int max_subtree = 0;
    for (int i : g[v]) {
      if (i != par[v]) {
        par[i] = v;
        depth[i] = depth[v] + 1;
        int sz[i] = dfs(g, i);
        if (subtree > max_subtree) {
          heavy[v] = i;
          max_subtree = sz[i];
        }
        sz[v] += sz[i];
      }
    }
  }

  void process_path(int u, int v, function<void(int, int)> f) {
    while (root[u] != root[v]) {
      if (depth[root[u]] > depth[root[v]]) {
        swap(u, v);
      }
      f(pos[root[v]], pos[v] + 1);
      v = par[root[v]];
    }
    if (depth[u] > depth[v]) {
      swap(u, v);
    }
    f(pos[u] + (edge_val ? 0 : 1), pos[v]);
  }

  void decompose() {
    int cur_pos = 0;
    for (int i = 0; i < n; i++) {
      if (par[i] == -1 || heavy[par[i]] != i) {
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          pos[j] = cur_pos++;
        }
      }
    }
  }

  template <typename G>
  HeavyLight(const G& g, bool _edge_val) : n(g.size()), edge_val(_edge_val) {
    assert(n > 0);
    heavy.resize(n, -1);
    par.resize(n);
    depth.resize(n);
    root.resize(n);
    pos.resize(n);
    dfs(g, 0);
    decompose();
    segtree<T, T> tree(n);
  }

  void modify_subtree(int v, int x) {
    tree.update(pos[v] + (edge_val ? 0 : 1), pos[v] + sz[v] - 1, v);
  }

  void modify_path(int u, int v, const T& x) {
    process_path(u, v, [this, &x](int l, int r) {
      tree.update(l, r, x);
    });
  }

  void query(int u, int v) {
    T res{};
    process_path(u, v, [this, &res](int l, int r) {
      res.unite(res, tree.query(l, r));
    });
  }
};
