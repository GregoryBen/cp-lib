// unweighted

class Tree {
 public:
  int n, log_size;
  bool is_done;
  vector<int> depth, par;
  vector<vector<int>> anc, node;

  Tree(int _n) : n(_n) {
    assert(n > 0);
    is_done = false;
    node.resize(n);
  }

  void add(int u, int v) {
    assert(0 <= u && u <= n - 1 && 0 <= v && v <= n - 1);
    node[u].emplace_back(v);
    node[v].emplace_back(u);
  }

  void do_dfs(int u) {
    for (int v : node[u]) {
      if (v != par[u]) {
        depth[v] = depth[u] + 1;
        par[v] = u;
        do_dfs(v);
      }
    }
  }

  void do_bfs() {
    queue <int> q;
    q.push(0);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : node[u])
        if (v != par[u]) {
          depth[v] = depth[u] + 1;
          par[v] = u;
          q.push(v);
        }
    }
  }

  void dfs() {
    depth.resize(n, 0);
    par.resize(n, -1);
    do_dfs(0);
    is_done = true;
  }

  void bfs() {
    depth.resize(n, 0);
    par.resize(n, -1);
    do_bfs();
    is_done = true;
  }

  void init_lca() {
    assert(is_done);
    log_size = 33 - __builtin_clz(n);
    anc.resize(log_size, vector<int>(n));
    for (int i = 0; i < n; i++) {
      anc[0][i] = par[i];
    }
    for (int i = 1; i < log_size; i++) {
      for (int u = 0; u < n; u++) {
        anc[i][u] = (anc[i - 1][u] == -1 ? -1 : anc[i - 1][anc[i - 1][u]]);
      }
    }
  }

  int get_lca(int u, int v) {
    assert(is_done && 0 <= u && u <= n - 1 && 0 <= v && v <= n - 1);
    if (depth[v] > depth[u]) {
      swap(u, v);
    }
    for (int i = log_size - 1; i >= 0; i--) {
      if (depth[u] - depth[v] >= (1 << i)) {
        u = anc[i][u];
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = log_size - 1; i >= 0; i--) {
      if (anc[i][u] != anc[i][v]) {
        u = anc[i][u];
        v = anc[i][v];
      }
    }
    return anc[0][u];
  }

  int do_diameter(int u, int& d) {
    int x = 0;
    for (int v : node[u]) {
      if (v != par[u]) {
        par[v] = u;
        depth[v] = depth[u] + 1;
        int y = do_diameter(v, d);
        d = max(d, x + y + 1);
        x = max(x, y);
      }
    }
    return x + 1;
  }

  int get_diameter() {
    int d = 0;
    do_diameter(0, d);
    is_done = true;
    return (d == 0 ? 0 : d - 1);
  }
};
