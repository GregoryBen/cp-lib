// incomplete
// hld 0 index and subtree update

template <typename T, typename L>
struct HeavyLight : segtree<T, L> {
  using segtree<T, L>::n;
  using segtree<T, L>::unite;
  using segtree<T, L>::update;
  using segtree<T, L>::query;

  bool is_node;
  vector<int> par;
  vector<int> heavy;
  vector<int> sz;
  vector<int> depth;
  vector<int> root;
  vector<int> pos;

  template <typename G>
  void dfs(const G& g, int v) {
    int max_subtree = 0;
    sz[v] = 1;
    for (int i : g[v]) {
      if (i != par[v]) {
        par[i] = v;
        depth[i] = depth[v] + 1;
        dfs(g, i);
        if (sz[i] > max_subtree) {
          heavy[v] = i;
          max_subtree = sz[i];
        }
        sz[v] += sz[i];
      }
    }
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

  void process_path(int u, int v, function<void(int, int)> f) {
    for (; root[u] != root[v]; v = par[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) {
        swap(u, v);
      }
      cerr << pos[root[v]] << ' ' << pos[v] << '\n';
      f(pos[root[v]], pos[v]);
      cerr << "done" << '\n';
    }
    if (depth[u] > depth[v]) {
      swap(u, v);
    }
    f(pos[u] + (is_node ? 0 : 1), pos[v]);
  }

  template <typename G>
  HeavyLight(const G& g, bool _is_node) : segtree<T, L>(g.size()), is_node(_is_node) {
    assert(n > 0);
    par.resize(n, -1);
    heavy.resize(n, -1);
    sz.resize(n);
    depth.resize(n);
    root.resize(n);
    pos.resize(n);
    dfs(g, 0);
    decompose();
    }

//  void update_subtree(int v, const L& x) { // (?)
//    update(pos[v] + (is_node ? 0 : 1), pos[v] + sz[v] - 1, x);
//  }

  void update_path(int u, int v, const L& x) {
    process_path(u, v, [this, &x](int l, int r) {
      update(l, r, x);
    });
  }

  T query_path(int u, int v) {
    T res{};
    process_path(u, v, [this, &res](int l, int r) {
      unite(res, query(l, r));
    });
    return res;
  }
};
