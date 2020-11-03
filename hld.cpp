// hld 0 index, subtree update and query

template <typename T, typename L>
struct HeavyLight : public segtree<T, L> {
  using segtree<T, L>::n;
  using segtree<T, L>::unite;
  using segtree<T, L>::update;
  using segtree<T, L>::query;

  int timer;
  bool is_node;
  vector<int> pos;
  vector<int> par;
  vector<int> root;
  vector<int> depth;
  vector<int> sz;
  vector<int> rpos;
  vector<vector<int>> g;

  void dfs_sz(int v) {
    sz[v] = 1;
    for (int i : g[v]) {
      par[i] = v;
      depth[i] = depth[v] + 1;
      g[i].erase(find(g[i].begin(), g[i].end(), v));
      dfs_sz(i);
      sz[v] += sz[i];
      if (sz[i] > sz[g[v][0]]) {
        swap(i, g[v][0]);
      }
    }
  }

  void dfs_hld(int v) {
    pos[v] = timer++;
    rpos.emplace_back(v);
    for (int i : g[v]) {
      root[i] = (i == g[v][0] ? root[v] : i);
      dfs_hld(i);
    }
  }

  int lca(int u, int v) {
    for(; root[u] != root[v]; v = par[root[v]]) {
      if(depth[root[u]] > depth[root[v]]) {
        swap(u, v);
      }
    }
    return depth[u] < depth[v] ? u : v;
  }

  int dist(int u, int v, int w = -1) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
  }

  void process_path(int u, int v, function<void(int, int)> f) {
    for (; root[u] != root[v]; v = par[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) {
        swap(u, v);
      }
      f(pos[root[v]], pos[v]);
    }
    if (u != v || is_node) {
      int a = min(pos[u], pos[v]);
      int b = max(pos[u], pos[v]);
      int add =  (is_node ? 0 : 1);
      f(a + add, b);
    }    
  }

  template <typename G>
  HeavyLight(const G& _g, bool _is_node, int r = 0) : segtree<T, L>(_g.size()) {
    assert(n > 0);
    timer = 0;
    is_node = _is_node;
    pos.resize(n);
    par.resize(n, -1);
    root.resize(n, r);
    depth.resize(n);
    sz.resize(n);
    g = _g;
    dfs_sz(r);
    root[r] = r;
    dfs_hld(r);
  }

  void update_subtree(int v, const L& x) {
    update(pos[v] + (is_node ? 0 : 1), pos[v] + sz[v] - 1, x);
  }

  void update_path(int u, int v, const L& x) {
    process_path(u, v, [this, &x](int l, int r) {
      update(l, r, x);
    });
  }
  
  T query_subtree(int v) {
    return query(pos[v] + (is_node ? 0 : 1), pos[v] + sz[v] - 1);

  T query_path(int u, int v) {
    T res{};
    process_path(u, v, [this, &res](int l, int r) {
      res = unite(res, query(l, r));
    });
    return res;
  }
};
