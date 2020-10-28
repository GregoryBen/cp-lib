struct centroid {
  int n;
  vector<int> sz;
  vector<int> par;
  vector<bool> dead;

  template <typename G>
  int one_centroid(int root, const G& g) {
    function<void(int, int)> dfs_sz = [&](int v, int p) {
      sz[v] = 1;
      for (int i : g[v]) {
        if (i != p && !dead[i]) {
          dfs_sz(i, v);
          sz[v] += sz[i];
        }
      }
    };
    dfs_sz(root, -1);
    int nk = sz[root];
    function<int(int, int)> dfs = [&](int v, int p) {
      for (int i : g[v]) {
        if (i != p && !dead[i]) {
          if (sz[i] > nk / 2) {
            return dfs(i, v);
          }
        }
      }
      return v;
    };
    return dfs(root, -1);
  }

  template <typename G>
  centroid(const G& g) : n(g.size()) {
    assert(n > 0);
    sz.resize(n);
    par.resize(n);
    dead.resize(n);
    dfs_centroid(0, -1, g);
  }

  template <typename G>
  void dfs_centroid(int v, int p, const G& g) {
    int c = one_centroid(v, g);
    par[v] = p;
    dead[c] = true;
    /* compute centroid data */

    /* compute centroid data */
    for (int i : g[c]) {
      if (!dead[i]) {
        dfs_centroid(i, c, g);
      }
    }
    /* compute centroid */

    /* compute centroid */
    dead[c] = false;
  }
};
