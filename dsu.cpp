struct dsu {
  int n;
  vector<int> link;

  dsu(int _n) : n(_n) {
    link.resize(n);
    iota(link.begin(), link.end(), 0);
  }

  inline int find(int x) {
    return (x == link[x] ? x : (link[x] = find(link[x])));
  }

  bool same(int a, int b) {
    return find(a) == find(b);
  }

  inline bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      link[a] = b;
      return true;
    }
    return false;
  }
};
