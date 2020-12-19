vector<int> euler_walk(const vector<vector<pair<int, int>>> &g, int m, int sc = 0) {
  int n = g.size();
  assert(n > 0);
  vector<int> D(n);
  vector<int> its(n);
  vector<int> eu(m);
  vector<int> res;
  stack<int> s;
  s.push(sc);
  D[sc]++;
  while (!s.empty()) {
    int x = s.top();
    if (its[x] == (int) g[x].size()) {
      res.push_back(x);
      s.pop();
      continue;
    }
    int y, e;
    tie(y, e) = g[x][its[x]++];
    if (!eu[e]) {
      D[x]--;
      D[y]++;
      eu[e] = 1;
      s.push(y);
    }
  }
  if ((int) res.size() != m + 1) {
    return vector<int>();
  }
  for (int x : D) {
    if (x < 0) {
      return vector<int>();
    }
  }
  return vector<int>(res.rbegin(), res.rend());
}
