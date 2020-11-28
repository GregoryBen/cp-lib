// credit : CPH
// O(n)

template <typename T>
vector<int> z_function(const T &s) {
  int n = s.size();
  vector<int> z(n);
  int x = 0, y = 0;
  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(z[i - x], y - i + 1));
    if (i + z[i] < y) continue;
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      x = i;
      y = i + z[i];
      z[i]++;
    }
  }
  return z;
}

// convert z_function to prefix

template <typename T>
vector<int> getPrefix(const T& s) {
  int n = (int) s.size();
  vector<int> p(n);
  vector<int> z = z_function(s);
  for (int i = 1; i < n; i++) {
    p[i + z[i] - 1] = max(p[i + z[i] - 1], z[i]);
  }
  for (int i = n - 2; i > 0; i--) {
    p[i] = max(p[i + 1] - 1, p[i]);
  }
  return p;
}
