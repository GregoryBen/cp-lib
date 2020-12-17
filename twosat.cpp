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

  void add(int x, bool val_x) {
    assert(0 <= x && x <= n - 1);
    g[2 * x + (val_x ^ 1)].emplace_back(2 * x + val_x);
  }

  void add(int x, bool val_x, int y, bool val_y) {
    assert(0 <= x && x <= n - 1 && 0 <= y && y <= n - 1);
    g[2 * x + (val_x ^ 1)].emplace_back(2 * y + val_y);
    g[2 * x + (val_y ^ 1)].emplace_back(2 * x + val_x);
  }

  void reverse(vector<vector<int>> &gr) {
    gr.resize(2 * n);
    for (int i = 0; i < n; i++) {
      for (int j : g[i]) {
        gr[j].emplace_back(i);
      }
    }
  }

  bool solve() {
    int cnt = 0;
    ans.assign(n, -1);
    vector<vector<int>> gr;
    reverse(gr);
    vector<int> c = get_scc(g, gr, cnt);
    for (int i = 0; i < n; i++) {
      if (c[2 * i] == c[2 * i + 1]) {
        return false;
      }
    }
    return true;
  }
};
