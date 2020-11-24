// preprocessing : O(n log n log(max(A))
// query : (log(max(A))
// max(A) : maximum element in array
// ex comp : [&](int i, int j) { return i < j; }; (default)

// [l, r], k, 0-based
// kth : smallest element in [l, r]
// LTE : number of elements in interval [L, R] that are less than or equal to y.
// count : number of occurrences of element x in interval [L, R]

template <typename T>
struct wavelet_node {
  T lo, hi;
  wavelet_node *l = nullptr;
  wavelet_node *r = nullptr;
  vector<int> b;

  template <typename IT, class C>
  wavelet_node(IT begin, IT end, T _lo, T _hi, const C& comp) : lo(_lo), hi(_hi) {
    if(begin >= end || lo == hi) {
      return;
    }
    T mid = lo + (hi - lo) / 2;
    auto f = [&](T x) {
      return comp(x, mid + 1);
    };
    b.reserve(end - begin + 1);
    b.emplace_back(0);
    for (auto it = begin; it != end; it++) {
      b.emplace_back(b.back() + f(*it));
    }
    auto pivot = stable_partition(begin, end, f);
    l = new wavelet_node(begin, pivot, lo, mid, comp);
    r = new wavelet_node(pivot, end, mid + 1, hi, comp);
  }
};

template <typename T, class C = function<bool(const T&, const T&)>>
struct wavelet_tree {
  int n;
  T mn, mx;
  wavelet_node<T> *root;
  C comp;

  template <typename IT>
  wavelet_tree(IT begin, IT end, const C& c = less<T>()) : n(end - begin), comp(c) {
    assert(n > 0);
    mn = *min_element(begin, end, comp);
    mx = *max_element(begin, end, comp);
    root = new wavelet_node<T>(begin, end, mn, mx, comp);
  }

  T kth(wavelet_node<T> *v, int l, int r, int k) {
    if (v->lo == v->hi) {
      return v->lo;
    }
    int lb = v->b[l];
    int rb = v->b[r + 1];
    int inLeft = rb - lb;
    return k < inLeft ? kth(v->l, lb, rb - 1, k) : kth(v->r, l - lb, r - rb, k - inLeft);
  }

  int LTE(wavelet_node<T> *v, int l, int r, T x) {
    if (l > r || !comp(v->lo, x)) {
      return 0;
    }
    if (comp(v->hi, x + 1)) {
      return r - l + 1;
    }
    int lb = v->b[l];
    int rb = v->b[r + 1];
    return LTE(v->l, lb, rb - 1, x) + LTE(v->r, l - lb, r - rb, x);
  }

  int count(wavelet_node<T> *v, int l, int r, T x) {
    if (l > r || comp(x, v->lo) || comp(v->hi, x)) {
      cerr << "out" << l << ' ' << r << ' ' << v->lo << ' ' << v->hi << '\n';
      return 0;
    }
    if (v->lo == v->hi) {
      return r - l + 1;
    }
    int lb = v->b[l];
    int rb = v->b[r + 1];
    T mid = v->lo + (v->hi - v->lo) / 2;
    return x <= mid ? count(v->l, lb, rb - 1, x) : count(v->r, l - lb, r - rb, x);
  }

  T kth(int l, int r, int k) {
    assert(0 <= l && l <= r && r <= n - 1 && 0 <= k && k <= n - 1);
    return kth(root, l, r, k);
  }

  int LTE(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n - 1 && mn <= x && x <= mx);
    return LTE(root, l, r, x);
  }

  int count(int l, int r, T x) {
    assert(0 <= l && l <= r && r <= n - 1 && mn <= x && x <= mx);
    return count(root, l, r, x);
  }

  void debug_tree() {
    #ifdef LOCAL
      deque<wavelet_node<T>*> d = {root};
      while (!d.empty()) {
        auto v = d.front();
        d.pop_front();
        cerr << "range = [" << v->lo << ", " << v->hi << "], freq: ";
        for (auto x : v->b) {
          cerr << x << " ";
        }
        cerr << '\n';
        if (v->l != nullptr) {
          d.emplace_back(v->l);
        }
        if (v->r != nullptr) {
          d.emplace_back(v->r);
        }
      }
    #endif
  }
};
