// Scaling O(VE log(U) with higher constant
// non-scaling O(V^2 E) (default)

|template <typename T, bool S>
struct dinic {
  struct edge {
    int to, rev;
    T c, f;
  };

  const T INF = numeric_limits<T>::max();

  int n, s, t, lim;
  vector<int> d;
  vector<int> ptr;
  vector<vector<edge>> g;

  dinic(int _n) : n(_n) {
    g.resize(n);
    d.resize(n);
    ptr.resize(n);
    lim = 1;
  }

  void clear_flow() {
    for (int i = 0; i < n; i++) {
      for (edge &e : g[i]) {
        e.f = 0;
      }
    }
    lim = 1;
  }

  void add(int a, int b, T c, T cr) {
    assert(0 <= a && a <= n - 1 && 0 <= b && b <= n - 1);
    int a_size = g[a].size();
    int b_size = g[b].size();
    g[a].push_back({b, b_size, c, 0});
    g[b].push_back({a, a_size, cr, 0});
  }

  bool dinic_bfs() {
    fill(d.begin(), d.end(), -1);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty() && d[t] == -1) {
      int u = q.front();
      q.pop();
      for (edge &e : g[u]) {
        int v = e.to;
        if (d[v] == -1 && e.f < e.c && (!S || e.c - e.f >= lim)) {
          d[v] = d[u] + 1;
          q.push(v);
        }
      }
    }
    return d[t] >= 0;
  }

  T dinic_dfs(int v, T flow) {
    if (v == t || !flow) {
      return flow;
    }
    for (int &i = ptr[v]; i < (int) g[v].size(); i++) {
      edge &e = g[v][i];
      if (d[e.to] != d[v] + 1) {
        continue;
      }
      T df = dinic_dfs(e.to, min(flow, e.c - e.f));
      if (df > 0) {
        e.f += df;
        g[e.to][e.rev].f -= df;
        return df;
      }
    }
    return 0;
  }

  long long max_flow(int src, int dest) {
    assert(0 <= src && src <= n - 1 && 0 <= dest && dest <= n - 1);
    s = src; t = dest;
    long long flow = 0;
    for (lim = S ? (1 << 30) : 1; lim > 0; lim >>= 1) {
      while (dinic_bfs()) {
        fill(ptr.begin(), ptr.end(), 0);
        while (true) {
          T delta = dinic_dfs(s, INF);
          if (delta == 0) {
            break;
          }
          flow += delta;
        }
      }
    }
    return flow;
  }

  vector<bool> min_cut() {
    vector<bool> cut(n);
    for (int i = 0; i < n; i++) {
      cut[i] = d[i] != -1;
    }
    return cut;
  }
};
