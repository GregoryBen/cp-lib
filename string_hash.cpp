struct string_hash {
  const int A = 31;
  const int B = (int) 1e9 + 9;

  int n;
  vector<int> h;
  vector<int> p;

  string_hash(const string &s) : n((int) s.size()) {
    assert(n > 0);
    h.resize(n);
    p.resize(n);
    h[0] = s[0] - 'a' + 1;
    p[0] = 1;
    for (int i = 1; i < n; i++) {
      h[i] = ((long long) h[i - 1] * A + s[i] - 'a' + 1) % B;
      p[i] = (long long) p[i - 1] * A % B;
    }
  }

  int get_hash(int l, int r) {
    assert(0 <= l && l <= r && r <= n - 1);
    return (r == 0 ? h[r] : (int) ((h[r] - (long long) h[l - 1] * p[r - l + 1]) % B));
  }
};
