// author : Simon Lindholm
// deg = indegree - outdegree

vector<int> euler_walk(const vector<vector<pair<int, int>>> &g, int m, int sc = 0) {
  int n = g.size();
  vector<int> deg(n);
  vector<int> at(n);
  vector<bool> vis(m);
  vector<int> res;
  stack<int> s;
  s.push(sc);
  deg[sc]++;
  while (!s.empty()) {
    int x = s.top();
    if (at[x] == (int) g[x].size()) {
      res.push_back(x);
      s.pop();
      continue;
    }
    int y, e;
    tie(y, e) = g[x][at[x]++];
    if (!vis[e]) {
      deg[x]--;
      deg[y]++;
      vis[e] = true;
      s.push(y);
    }
  }
  if ((int) res.size() != m + 1) {
    return vector<int>();
  }
  for (int x : deg) {
    if (x < 0) {
      return vector<int>();
    }
  }
  return vector<int>(res.rbegin(), res.rend());
}

// more strightforward, but destroy graph

vector<int> euler_walk(vector<vector<pair<int, int>>> &g, int m, int sc = 0) {
  bool bad = false;
  vector<int> vis(m);
  vector<pair<int, int>> res;
  function<void(int, int)> dfs = [&](int p, int i) {
    while (!g[i].empty()) {
      auto [j, e] = g[i].back();
      g[i].pop_back();
      if (!vis[e]) {
        vis[e] = true;
        dfs(i, j);
      }
    }
    if (!res.empty() && res.back().first != i) {
      bad = true;
    }
    res.emplace_back(p, i);
  };
  dfs(-1, sc);
  if ((int) res.size() != m + 1 || bad) {
    return vector<int>();
  }
  debug(res);
  vector<int> ans(m + 1);
  for (int i = m; i >= 0; i--) {
    ans[m - i] = res[i].second;
  }
  return ans;
}
