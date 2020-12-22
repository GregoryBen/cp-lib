// faster than Hopcroft Karp BPM in a random graph but slower in a d-regular graph
// O(EV) in d-regular graph

|struct matching {
  int n, m, res;
  vector<int> left;
  vector<int> right;
  vector<bool> vis;
  vector<vector<int>> g;

  matching(int _n, int _m) : n(_n), m(_m) {
    assert(n >= 0 && m >= 0);
    left.resize(n, -1);
    right.resize(m, -1);
    vis.resize(n);
    g.resize(n);
  }

  void add(int u, int v) {
    assert(0 <= u && u <= n - 1 && 0 <= v && v <= m - 1);
    g[u].emplace_back(v);
  }

  bool match(int u) {
    if (vis[u]) {
      return false;
    }
    vis[u] = true;
    for (int v : g[u]) {
      if (right[v] == -1) {
        left[u] = v;
        right[v] = u;
        return true;
      }
    }
    for (int v : g[u]) {
      if (match(right[v])) {
        left[u] = v;
        right[v] = u;
        return true;
      }
    }
    return false;
  }

  int find_match() {
    while (true) {
      int add = 0;
      vis.assign(n, false);
      for (int i = 0; i < n; i++) {
        if (left[i] == -1 && match(i)) {
          add++;
        }
      }
      if (add == 0) {
        break;
      }
      res += add;
    }
    return res;
  }
};
