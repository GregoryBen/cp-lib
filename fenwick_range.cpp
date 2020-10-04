|template <typename T>
struct fenwick_range {
  int n;
  vector<T> data_mul, data_add;

  fenwick_range(int _n) : n(_n) {
    assert(n > 0);
    data_mul.resize(n);
    data_add.resize(n);
  }

  template <typename IT>
  fenwick_range(IT begin, IT end) : n(end - begin) {
    data_mul.resize(n);
    data_add.resize(n);
    for (int i = 0; i < n; i++) {
      update(i, i, *(begin++));
    }
  }

  void update_bit(int k, T mul, T add) {
    while (k < n) {
      data_mul[k] += mul;
      data_add[k] += add;
      k |= (k + 1);
    }
  }

  void update(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n - 1);
    update_bit(l, x, -x * (l - 1));
    update_bit(r, -x, x * r);
  }

  T query(int k) {
    T mul{}, add{};
    T start = k;
    while (k >= 0) {
      mul += data_mul[k];
      add += data_add[k];
      k = (k & (k + 1)) - 1;
    }
    return mul * start + add;
  }

  T query(int l, int r) {
    assert(0 <= l && l <= r && r <= n - 1);
    return query(r) - query(l - 1);
  }
};
