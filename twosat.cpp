// require get_scc (tarjan)

struct twosat {
  int n;
  vector<int> ans;
  vector<vector<int>> g;

  twosat(int _n) : n(_n) {
    g.resize(2 * n);
  }

  template <typename G>
  twosat(const G &_g) {
    n = g.size() / 2;
    g = _g;
  }

  void add(int x, bool vx) {
    assert(0 <= x && x <= n - 1);
    g[2 * x + (vx ^ 1)].emplace_back(2 * x + vx);
  }

  void add(int x, bool vx, int y, bool vy) {
    assert(0 <= x && x <= n - 1 && 0 <= y && y <= n - 1);
    g[2 * x + (vx ^ 1)].emplace_back(2 * y + vy);
    g[2 * y + (vy ^ 1)].emplace_back(2 * x + vx);
  }

  bool solve() {
    int cnt = 0;
    ans.assign(n, -1);
    vector<int> c = get_scc(g, cnt);
    for (int i = 0; i < n; i++) {
      if (c[2 * i] == c[2 * i + 1]) {
        return false;
      }
      ans[i] = (c[2 * i] < c[2 * i + 1]);
    }
    return true;
  }
};
