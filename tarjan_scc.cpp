vector<int> tarjan_scc(const vector<vector<int>> &g, int &cnt) {
  int n = g.size();
  int time = 0;
  vector<int> c(n);
  vector<int> low(n);
  vector<int> vis_time(n, -1);
  vector<bool> vis(n);
  stack<int> s;
  function<void(int)> dfs = [&](int i) {
    vis_time[i] = low[i] = time;
    time++;
    s.emplace(i);
    vis[i] = true;
    for (int j : g[i]) {
      if (vis_time[j] == -1) {
        dfs(j);
      }
      if (vis[j]) {
        low[i] = min(low[i], low[j]);
      }
    }
    if (vis_time[i] == low[i]) {
      while (vis[i]) {
        int t = s.top();
        c[t] = i;
        vis[t] = false;
        s.pop();
      }
    }
  };
  for (int i = 0; i < n; i++) {
    if (vis_time[i] == -1) {
      dfs(i);
    }
  }
  vector<int> d(n, -1);
  for (int i = 0; i < n; i++) {
    if (d[c[i]] == -1) {
      d[c[i]] = cnt++;
    }
    c[i] = d[c[i]];
  }
  return c;
}
