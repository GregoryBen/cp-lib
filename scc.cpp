// kosaraju

vector<int> get_scc(const vector<vector<int>> &g, const vector<vector<int>> &gr, int &cnt) {
  int n = g.size();
  vector<bool> vis(n);
  vector<int> topo;
  function<void(int)> dfs = [&](int i) {
    vis[i] = true;
    for (int j : g[i]) {
      if (!vis[j]) {
        dfs(j);
      }
    }
    topo.emplace_back(i);
  };
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }
  vector<int> c(n, -1);
  function<void(int)> dfs1 = [&](int i) {
    for (int j : gr[i]) {
      if (c[j] == -1) {
        c[j] = c[i];
        dfs1(j);
      }
    }
  };
  for (int i = n - 1; i >= 0; i--) {
    int k = topo[i];
    if (c[k] != -1) {
      continue;
    }
    c[k] = cnt++;
    dfs1(k);
  }
  return c;
}

// tarjan

vector<int> get_scc(const vector<vector<int>> &g, int &cnt) {
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
        c[t] = cnt;
        vis[t] = false;
        s.pop();
      }
      cnt++;
    }
  };
  for (int i = 0; i < n; i++) {
    if (vis_time[i] == -1) {
      dfs(i);
    }
  }
  for (int& x : c) {
    x = cnt - 1 - x;
  }
  return c;
}
