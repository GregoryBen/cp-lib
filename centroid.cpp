// find centroid

vector<int> find_centroid(const vector<vector<int>>& g) {
  int n = g.size();
  assert(n > 0);
  vector<int> sz(n);
  vector<int> cen;
  function<void(int, int)> dfs = [&](int v, int p) {
    sz[v] = 1;
    bool is_cen = true;
    for (int i : g[v]) {
      if (i != p) {
        dfs(i, v);
        sz[v] += sz[i];
        if (sz[i] > n / 2) {
          is_cen = false;
        }
      }
    }
    if (n - sz[v] > n / 2) is_cen = false;
    if (is_cen) cen.push_back(v);
  };
  dfs(0, -1);
  assert(cen.size() <= 2);
  return cen;
}

// find one centroid with death node/edge

int one_centroid(int root, const vector<vector<int>>& g, const vector<bool>& dead) {
  assert(!g.empty());
  vector<int> sz(g.size());
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
  int n = sz[root];
  function<int(int, int)> dfs = [&](int v, int p) {
    for (int i : g[v]) {
      if (i != p && !dead[i]) {
        if (sz[i] > n / 2) {
          return dfs(i, v);
        }
      }
    }
    return v;
  };
  return dfs(root, -1);
}
