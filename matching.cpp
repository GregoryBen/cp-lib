class matching {
 public:
  int n, m;
  vector<int> left, right, vis;
  vector<vector<int>> node;

  matching(int _n, int _m) : n(_n), m(_m) {
    node.resize(n);
    left.resize(n, -1);
    right.resize(m, -1);
    vis.resize(n);
  }

  void add(int u, int v) {
    node[u].push_back(v);
  }

  bool match(int u) {
    if (vis[u]) {
      return false;
    }
    vis[u] = 1;
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
      for (int i = 0; i < n; i++) {
        vis[i] = 0;
      }
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
