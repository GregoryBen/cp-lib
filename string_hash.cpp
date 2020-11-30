struct hashing {
  static constexpr int dim = 4;
  static constexpr int md = (1u << 31) - 1;

  int n;
  vector<vector<int>> h;
  vector<vector<int>> p;

  static const vector<int> &get_bases() {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    static vector<int> bases;
    while (bases.size() < dim) {
      bases.emplace_back(uniform_int_distribution<int>((int) 1e9, md - 1)(rng));
    }
    return bases;
  }

  hashing(const string &s) : n((int) s.size()) {
    assert(n > 0);
    h.resize(dim);
    p.resize(dim);
    const vector<int> &bases = get_bases();
    for (int d = 0; d < dim; d++) {
      h[d].resize(n + 1);
      p[d].resize(n + 1);
      p[d][0] = 1;
      long long base = bases[d];
      for (int i = 0; i < n; i++) {
        h[d][i + 1] = (h[d][i] * base + s[i]) % md;
        p[d][i + 1] = p[d][i] * base % md;
      }
    }
  }

  vector<int> get_hash(int i, int len) {
    assert(0 <= i && i + len <= n);
    vector<int> res(dim);
    for (int d = 0; d < dim; d++) {
      res[d] = (int) ((h[d][i + len] + (long long) h[d][i] * (md - p[d][len])) % md);
    }
    return res;
  }
};
