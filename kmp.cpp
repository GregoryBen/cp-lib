// kmp_table - O(|pattern|)

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

// kmp_search - O(|s|)

template <typename T>
vector<int> search(const T &w, const T &s, const vector<int> &p) {
  assert((int) w.size() > 0 && w.size() == p.size());
  int i = 0, j = 0;
  int m = (int) w.size();
  int n = (int) s.size();
  vector<int> res;
  while (i < n) {
    if (w[j] == s[i]) {
      i++; j++;
    }
    if (j == m) {
      res.emplace_back(i - j);
      j = p[j - 1];
    } else if (i < n && w[j] != s[i]) {
      if (j != 0) {
        j = p[j - 1];
      } else {
        i = i + 1;
      }
    }
  }
  return res;
}

// prefix automaton O(kn) k = |ALPHA|
// lowercase

vector<vector<int>> prefix_automaton(const string &s, const vector<int> &p) {
  assert((int) s.size() == (int) p.size());
  int n = (int) s.size();
  vector<vector<int>> aut(n, vector<int>(26));
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && c + 'a' != s[i]) {
        aut[i][c] = aut[p[i - 1]][c];
      } else {
        aut[i][c] = i + (c + 'a' == s[i]);
      }
    }
  }
  return aut;
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
