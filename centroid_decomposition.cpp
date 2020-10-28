struct centroid {
  int n;
  vector<int> sz;
  vector<int> cpar;
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
    cpar.resize(n);
    dead.resize(n);
    dfs_centroid(0, -1, g);
  }

  template <typename G>
  void dfs_centroid(int v, int p, const G& g) {
    int c = one_centroid(v, g);
    cpar[c] = p;
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

// more complete

struct centroid {
  int n, croot;
  vector<int> sz;
  vector<int> cpar;
  vector<bool> dead;
  vector<vector<int>> cchild, dis;

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
  void dfs_dis(int v, int p, const G& g) {
    dis.emplace_back(dis[p].back() + 1);
    for (int i : g[v]) {
      if (v != p && !dead[i]) {
        dfs_dis(i, v, g);
      }
    }
  }

  template <typename G>
  centroid(const G& g) : n(g.size()) {
    assert(n > 0);
    sz.resize(n);
    cpar.resize(n);
    dead.resize(n);
    cchild.resize(n);
    dis.resize(n);
    dfs_centroid(0, -1, g);
  }

  template <typename G>
  void dfs_centroid(int v, int p, const G& g) {
    int c = one_centroid(v, g);
    cpar[c] = p;
    if (p != -1) {
      cchild[p].push_back(c);
    } else {
      croot = v;
    }
    dis[c].emplace_back(0);
    for (int i : g[c]) {
      if (!dead[i]) {
        dfs_dis(i, c, g);
      }
    }
    /* compute centroid data */

    /* compute centroid data */
    dead[c] = true;
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
