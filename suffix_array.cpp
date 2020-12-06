// O((n + k) log n) time, O(n) memory, k number of alphabet in input

template <typename T>
vector<int> suffix_array(const T &s) {
  int n = (int) s.size();
  vector<int> sa(n);
  for (int i = 0; i < n; i++) {
    sa[i] = n - i - 1;
  }
  stable_sort(sa.begin(), sa.end(), [&](int i, int j) {
    return s[i] < s[j];
  });
  vector<int> group(s.begin(), s.end());
  for (int len = 1; len < n; len <<= 1) {
    vector<int> c = group;
    for (int i = 0; i < n; i++) {
      bool check = (i > 0 && c[sa[i - 1]] == c[sa[i]] && sa[i - 1] + len < n && c[sa[i - 1] + len / 2] == c[sa[i] + len / 2]);
      group[sa[i]] = (check ? group[sa[i - 1]] : i);
    }
    vector<int> cnt(n);
    iota(cnt.begin(), cnt.end(), 0);
    vector<int> cnt_s = sa;
    for (int i = 0; i < n; i++) {
      int s1 = cnt_s[i] - len;
      if (s1 >= 0)
        sa[cnt[group[s1]]++] = s1;
    }
  }
  return sa;
}

template <typename T>
vector<int> lcp_array(const T &s, vector<int> &sa) {
  assert((int) s.size() == (int) sa.size());
  int n = (int) s.size();
  vector<int> rank(n);
  for (int i = 0; i < n; i++) {
    rank[sa[i]] = i;
  }
  vector<int> lcp(n - 1);
  for (int i = 0, h = 0; i < n; i++) {
    if (rank[i] < n - 1) {
      for (int j = sa[rank[i] + 1]; s[i + h] == s[j + h]; h++) continue;
      lcp[rank[i]] = h;
      if (h > 0) {
        --h;
      }
    }
  }
  return lcp;
}
