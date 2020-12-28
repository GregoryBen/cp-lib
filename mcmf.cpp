// O(E * V + E * logV * FLOW)
// negative-cost edges are allowed
// negative-cost cycles are not allowed

template <typename T, typename C>
struct mcmf {
  struct edge {
    int to, rev;
    T cap, f;
    C cost;
  };

  int n;
  bool neg_cost;
  vector<vector<edge>> g;

  T flow;
  C flow_cost;

  mcmf(int _n) : n(_n), g(_n) {
    neg_cost = false;
  }

  void add(int s, int t, T cap, C cost) {
    assert(0 <= s && s <= n - 1 && 0 <= t && t <= n - 1);
    neg_cost |= (cost < 0);
    int s_size = g[s].size();
    int t_size = g[t].size();
    g[s].push_back({t, t_size, cap, 0, cost});
    g[t].push_back({s, s_size, 0, 0, -cost});
  }

  void clear_flow() {
    for (int i = 0; i < n; i++) {
      for (edge &e : g[i]) {
        e.f = 0;
      }
    }
    neg_cost = false;
    flow = 0;
    flow_cost = 0;
  }

  pair<T, C> cal_min_cost_flow(int s, int t, T maxf) {
    vector<int> pot(n), prevnode(n), prevedge(n);
    vector<C> dist(n);
    vector<T> curflow(n);
    if (neg_cost) {
      vector<int> q(n);
      vector<bool> inqueue(n);
      fill(dist.begin(), dist.end(), numeric_limits<C>::max());
      dist[s] = 0;
      int qt = 0;
      q[qt++] = s;
      for (int qh = 0; qh != qt; qh++) {
        int u = q[qh % n];
        inqueue[u] = false;
        for (edge &e : g[u]) {
          if (e.cap <= e.f) {
            continue;
          }
          int v = e.to;
          int ndist = dist[u] + e.cost;
          if (dist[v] > ndist) {
            dist[v] = ndist;
            if (!inqueue[v]) {
              inqueue[v] = true;
              q[qt++ % n] = v;
            }
          }
        }
      }
    }
    flow = 0;
    flow_cost = 0;
    while (flow < maxf) {
      priority_queue<pair<C, int>, vector<pair<C, int>>, greater<>> q;
      q.emplace(0, s);
      fill(dist.begin(), dist.end(), numeric_limits<C>::max());
      dist[s] = 0;
      curflow[s] = numeric_limits<T>::max();
      while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d != dist[u]) {
          continue;
        }
        for (int i = 0; i < (int) g[u].size(); i++) {
          edge &e = g[u][i];
          int v = e.to;
          if (e.cap <= e.f) {
            continue;
          }
          int nprio = dist[u] + e.cost + pot[u] - pot[v];
          if (dist[v] > nprio) {
            dist[v] = nprio;
            q.emplace(nprio, v);
            prevnode[v] = u;
            prevedge[v] = i;
            curflow[v] = min(curflow[u], e.cap - e.f);
          }
        }
      }
      if (dist[t] == numeric_limits<C>::max()) {
        break;
      }
      for (int i = 0; i < n; i++) {
        pot[i] += dist[i];
      }
      T df = min(curflow[t], maxf - flow);
      flow += df;
      for (int v = t; v != s; v = prevnode[v]) {
        edge &e = g[prevnode[v]][prevedge[v]];
        e.f += df;
        g[v][e.rev].f -= df;
        flow_cost += df * e.cost;
      }
    }
    return {flow, flow_cost};
  }
};
