// O(n) call dinic's max_flow

template <typename T, bool S>
vector<vector<pair<int, int>>> gomory_hu(dinic<long long, false> &g) {
  int n = g.n;
  vector<vector<pair<int, int>>> t(n);
  vector<int> p(n);
  for (int i = 1; i < n; i++) {
    g.clear_flow();
    int f = g.max_flow(i, p[i]);
    vector<bool> cut = g.min_cut();
    for (int j = i + 1; j < n; j++) {
      if (cut[j] == cut[i] && p[j] == p[i]) {
        p[j] = i;
      }
    }
    t[p[i]].emplace_back(i, f);
  }
  return t;
}
