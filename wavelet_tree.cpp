// preprocessing : O(log n log(max(A))
// query : (log(max(A))
// max(A) :  maximum element in array
// ex comp : [&](int i, int j) { return i < j; };

template <typename T>
struct wavelet_node {
  int n;
  T lo, hi;
  wavelet_node *l = nullptr;
  wavelet_node *r = nullptr;
  vector<int> b;

  template <typename IT, class C>
  wavelet_node(IT begin, IT end, T _lo, T _hi, const C& comp) : n(end - begin), lo(_lo), hi(_hi) {
    if(n == 0 || lo == hi) {
      return;
    }
    T mid = lo + (hi - lo) / 2;
    auto f = [&](T x) {
      return comp(x, mid);
    };
    b.reserve(n + 1);
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
  wavelet_node<T> *root;
  C comp;

  template <typename IT>
  wavelet_tree(IT begin, IT end, const C& c) : n(end - begin), comp(c) {
    assert(n > 0);
    T min = *min_element(begin, end, comp);
    T max = *max_element(begin, end, comp);
    root = new wavelet_node<T>(begin, end, min, max, comp);
  }

  T kth(wavelet_node<T> *v, int l, int r, int k) {
    assert(0 <= k && k < v->n);
    if (v->lo == v->hi) {
      return v->lo;
    }
    int lb = v->b[l];
    int rb = v->b[r];
    int inLeft = rb - lb;
    return k <= inLeft ? kth(v->l, lb, rb, k) : kth(v->r, l - lb, r - rb, k - inLeft);
  }

  int LTE(wavelet_node<T> *v, int l, int r, T x) {
    if (l > r || !comp(v->lo, x)) {
      return 0;
    }
    if (!comp(x, v->hi)) {
      return r - l + 1;
    }
    int lb = v->b[l];
    int rb = v->b[r];
    return LTE(v->l, lb, rb, x) + LTE(v->r, l - lb, r - rb, x);
  }

  T kth(int l, int r, int k) {
    return kth(root, l, r, k);
  }

  int LTE(int l, int r, T x) {
    return LTE(root, l, r, x);
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
        cerr << "\n";
        if (v->l) {
          d.emplace_back(v->l);
        }
        if (v->r) {
          d.emplace_back(v->r);
        }
      }
    #endif
  }
};
