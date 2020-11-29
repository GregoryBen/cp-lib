// kmp 
// O(n)

template <typename T>
vector<int> prefix_function(const T &s) {
  int n = (int) s.size(), j = 0;
  vector<int> p(n);
  for(int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) {
      j = p[j - 1];
    }
    if(s[i] == s[j]) {
      j++;
    }
    p[i] = j;
  }
  return p;
}

// convert prefix to z
// maybe need prefix_function

vector<int> getZ(const vector<int> &p) {
  int n = (int) p.size();
  vector<int> z(n);
  for (int i = 1; i < n; i++) {
    if (p[i] > 0) {
      z[i - p[i] + 1] = p[i];
    }
  }
  if (z[1] > 0) {
    for (int i = 1; i < z[1]; i++) {
      z[i + 1] = z[1] - i;
    }
  }
  for (int i = z[1] + 1; i < n - 1; i++) {
    int t = i;
    if (z[i] && !z[i + 1]) {
      for (int j = 1; j < z[i] && z[i + j] <= z[j]; j++) {
        z[i + j] = min(z[j], z[i] - j);
        t = i + j;
      }
    }
    i = t;
  }
  return z;
}
