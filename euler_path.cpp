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
