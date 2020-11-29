// O(n)
// rotate(v.begin(), v.begin() + least_rotation(v), v.end())

template <typename T>
int least_rotation(T s) {
  int n = (int) s.size(), k = 0;
  for (int i = 0; i < n; i++) {
    s.push_back(s[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (k + j == i || s[k + j] < s[i + j]) {
        i += max(0, j - 1);
        break;
      }
      if (s[k + j] > s[i + j]) {
        k = i;
        break;
      }
    }
  }
  return k;
}
