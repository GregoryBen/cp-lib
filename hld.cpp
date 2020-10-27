// incomplete

template <typename T>
struct HeavyLight : public segtree {
  int n;
  vector<int> par, heavy, dis;
  vector<int> root, pos;

  int dfs(const vector<vector<int>>& g, int v) {
    int size = 1;
    int max_subtree = 0;
    for (int i : g[v]) {
      if (u != par[v]) {
        par[u] = v;
        dis[u] = dis[v] + 1;
        int subtree = dfs(g, u);
        if (subtree > max_subtree) {
          heavy[v] = u;
          max_subtree = subtree;
        }
      }
      size += subtree;
    }
    return size;
  }

  void process_path(int u, int v, function<) // (?)

  int build() { // (?)
    for (int i = 0, cur_pos = 0; i < n; i++) {
      if (par[i] = -1 || heavy[par[i]] != i) {
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          pos[j] = cur_pos++;
        }
      }
    }
  }

  HeavyLight(const vector<vector<int>>& g) : n(g.size()) {
    assert(n > 0);
    heavy.resize(n, -1);
    par.resize(n, -1);
    dis.resize(n);
    dfs(g, 0);
    build(); // (?)
    segtree<T, T> tree(n); // (?)
  }

  void

};
