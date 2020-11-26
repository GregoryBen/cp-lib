// kmp 
// O(n)

template <typename T>
vector<int> prefix_function(const T &s){
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

template <typename T>
vector<int> getZ(const T &s) {
  int n = (int) s.size();
  vector<int> z(n);
  vector<int> p = prefix_function(s);
  for (int i = 0; i < n - 1; i++) {
    debug(i, i - p[i] + 1);
    z[i - p[i] + 1] = max(z[i - p[i] + 1], p[i]);
  }
  for (int i = 1; i < n; i++) {
    z[i] = max(z[i - 1] - 1, z[i]);
  }
  return z;
}
