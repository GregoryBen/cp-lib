|namespace graph_generator {
  
vector<array<int, 2>> renaming(vector<array<int, 2>>& g, int n) {
  int m = g.size();
  vector<int> perm(n + 1);
  iota(perm.begin() + 1, perm.end(), 1);
  shuffle(perm.begin() + 1, perm.end(), rng);
  shuffle(g.begin(), g.end(), rng);
  vector<array<int, 2>> res(m);
  for (int i = 0; i < m; i++) {
      int a = g[i][0];
      int b = g[i][1];
      if (rand(0, 1)) {
          swap(a, b);
      }
      res[i][0] = perm[a];
      res[i][1] = perm[b];
  }
  return res;
}

vector<array<int, 2>> tree(int n) {
  vector<array<int, 2>> res(n - 1);
  for (int i = 2; i <= n; i++) {
    res[i - 2][0] = rand(1, i - 1);
    res[i - 2][1] = i;
  }
  res = renaming(res, n);
  return res;
}

vector<array<int, 2>> graph(int n, int m) {
  vector<array<int, 2>> res(m);
  for (int i = 0; i < m; i++) {
    res[i][0] = rng() % n + 1;
    res[i][1] = rng() % n + 1;
  }
  return res;
}

vector<array<int, 2>> simply_connected_graph(int n, int m) {
  assert(n - 1 <= m && m <= 1LL * n * (n - 1) / 2);
  auto res = tree(n);
  set<array<int, 2>> s;
  for (int i = 0; i < n - 1; i++) {
    s.insert({res[i][0], res[i][1]});
    s.insert({res[i][1], res[i][0]});
  }
  for(int i = n - 1; i < m; i++) {
    int u, v;
    do {
      u = rng() % n + 1;
      v = rng() % n + 1;
    } while (u == v || s.count({u, v}));
    s.insert({u, v});
    s.insert({v, u});
    res.push_back({u, v});
  }
  shuffle(res.begin(), res.end(), rng);
  return res;
}
  
} // namespace graph_generator

using namespace graph_generator;
