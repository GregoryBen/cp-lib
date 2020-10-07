// under construction!

template <typename Q, typename L, typename B = int>
struct dynamic_segtree {
  pair<Q, L> id = {0, 0};
  B left, right;
  Q tree;
  L lazy = id.second;
  dynamic_segtree *l = nullptr;
  dynamci_segtree *r = nullptr;

  Q unite(const node &a, const node &b) {
    Q res;
    ...
    return res;
  }

  void apply() { // under construction

  }

  void push() {
    B mid = left + (right - begin) / 2;
    if (l == nullptr) {
      l = new dynamic_segtree(left, mid);
    }
    if (r == nullptr) {
      r = new dynamic_segtree(mid + 1, right);
    }

  }

  dynamic_segtree(B _l, B _r) : left(_l), right(_r) {
  }

  template <typename It>
  dynamic_segtree(IT begin, IT end) : l(0), r(end - begin - 1) {
    assert(r > 0);
    build(begin, end, l, r);
  }

  ~dynamic_segtree() {
    delete l;
    delete r;
  }

  template <typename IT>
  void build(IT begin, IT end, B l, B r) {
    assert(end - begin == r - l + 1);
    if (l == r) {
      tree = *begin;
    }
    IT inter = begin + (end - begin) / 2;
    B m = l + (r - l) / 2;
    l = new dynamic_segtree(begin, inter, l, m);
    r = new dynamic_segtree(inter, end, m + 1, r);
    tree = unite(l -> tree, r -> tree);
  }


};
