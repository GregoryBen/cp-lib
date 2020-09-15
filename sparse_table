template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTb {
  int n;
  vector<vector<T>> tb;
  F func;

  template <typename IT>
  SparseTb(IT begin, IT end, const F& f) : n(end - begin), func(f) {
    int tb_size = 32 - __builtin_clz(n);
    tb.resize(tb_size);
    tb[0].resize(n);
    copy(begin, end, tb[0].begin());
    for (int j = 1; j < tb_size; j++) {
      tb[j].resize(n - (1 << j) + 1);
      for (int i = 0; i < (int) tb[j].size(); i++) {
        tb[j][i] = func(tb[j - 1][i], tb[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T query(int l, int r) {
    assert(0 <= l && l <= r && r <= n - 1);
    int d = 31 - __builtin_clz(r - l + 1);
    return func(tb[d][l], tb[d][r - (1 << d) + 1]);
  }
};
