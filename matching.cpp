|class matching {
 public:
  int n, m;
  vector<int> left, right;
  vector<bool> vis;
  vector<vector<int>> node;

  matching(int _n, int _m) : n(_n), m(_m) {
    assert(n > 0 && m > 0);
    node.resize(n);
    left.resize(n, -1);
    right.resize(m, -1);
    vis.resize(n);
  }

  void add(int u, int v) {
    assert(0 <= u && u <= n - 1 && 0 <= v && v <= n -1);
    node[u].emplace_back(v);
  }

  bool match(int u) {
    if (vis[u]) {
      return false;
    }
    vis[u] = true;
    for (int v : node[u]) {
      if (right[v] == -1) {
        left[u] = v;
        right[v] = u;
        return true;
      }
    }
    for (int v : node[u]) {
      if(match(right[v])) {
        left[u] = v;
        right[v] = u;
        return true;
      }
    }
    return false;
  }

  void find_match() {
    bool ok = true;
    while (ok) {
      ok = false;
      vis.assign(n, false);
      for (int i = 0; i < n; i++) {
        if (left[i] == -1) {
          ok |= match(i);
        }
      }
    }
  }

  int max_match() {
    int res = 0;
    for (int i = 0; i < n; i++) {
      res += (left[i] != -1);
    }
    return res;
  }
};
