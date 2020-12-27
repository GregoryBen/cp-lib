// faster than dinic
// limitation : can't recover the weights for the full flow - use Dinic's for this.

template <typename T>
struct hlpp {
  struct edge {
    int to, rev;
    T f;
  };
 
  const T INF = numeric_limits<T>::max();
 
  int n, s, t;
  int highest, work;
  vector<int> height;
  vector<int> cnt;
  vector<T> excess;
  vector<vector<int>> lst;
  vector<vector<int>> gap;
  vector<vector<edge>> g;
 
  hlpp(int _n) : n(_n) {
    g.resize(n);
    lst.resize(n + 1);
    gap.resize(n);
    excess.resize(n);
    height.resize(n);
    cnt.resize(n);
    highest = 0;
  }
 
  void add(int a, int b, T f, T fr) {
    assert(0 <= a && a <= n - 1 && 0 <= b && b <= n - 1);
    int a_size = g[a].size();
    int b_size = g[b].size();
    g[a].push_back({b, b_size, f});
    g[b].push_back({a, a_size, fr});
  }
 
  void updHeight(int v, int nh) {
    work++;
    if (height[v] != n) {
      cnt[height[v]]--;
    }
    height[v] = nh;
    if (nh == n) {
      return;
    }
    cnt[nh]++;
    highest = nh;
    gap[nh].push_back(v);
    if (excess[v] > 0) {
      lst[nh].push_back(v);
    }
  }
 
  void globalRelabel() {
    work = 0;
    fill(height.begin(), height.end(), n);
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < highest; i++) {
      lst[i].clear();
      gap[i].clear();
    }
    height[t] = 0;
    queue<int> q;
    q.push(t);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (edge &e : g[v]) {
        if (height[e.to] == n && g[e.to][e.rev].f > 0) {
          q.push(e.to);
          updHeight(e.to, height[v] + 1);
        }
      }
      highest = height[v];
    }
  }
 
  void push(int v, edge &e) {
    if (excess[e.to] == 0) {
      lst[height[e.to]].push_back(e.to);
    }
    T df = min(excess[v], e.f);
    e.f -= df;
    g[e.to][e.rev].f += df;
    excess[v] -= df;
    excess[e.to] += df;
  }
 
  void discharge(int v) {
    int nh = n;
    for (edge &e : g[v]) {
      if (e.f > 0) {
        if (height[v] == height[e.to] + 1) {
          push(v, e);
          if (excess[v] <= 0) {
            return;
          }
        } else {
          nh = min(nh, height[e.to] + 1);
        }
      }
    }
    if (cnt[height[v]] > 1) {
      updHeight(v, nh);
    } else {
      for (int i = height[v]; i <= highest; i++) {
        for (int j : gap[i]) {
          updHeight(j, n);
        }
        gap[i].clear();
      }
    }
  }
 
  T max_flow(int src, int dest) {
    assert(0 <= src && src <= n - 1 && 0 <= dest && dest <= n - 1);
    fill(excess.begin(), excess.end(), 0);
    s = src; t = dest;
    excess[s] = INF;
    excess[t] = -INF;
    globalRelabel();
    for (edge &e : g[s]) {
      push(s, e);
    }
    do {
      while (!lst[highest].empty()) {
        int v = lst[highest].back();
        lst[highest].pop_back();
        discharge(v);
        if (work > 4 * n) {
          globalRelabel();
        }
      }
      highest--;
    } while (0 <= highest);
    return excess[t] + INF;
  }
