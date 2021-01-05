// (max value * ADD) must fit in long long

template <typename T>
struct ordered_multiset {
  const int ADD = (int) 1e6 + 10;
  const int MAXVAL = (int) 1e9 + 10;

  int len;
  gp_hash_table<long long, int, my_hash> mp;
  tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> t;

  ordered_multiset() {
    len = 0;
  }

  inline void clear() {
    len = 0;
    t.clear();
    mp.clear();
  }

  inline void insert(T v) {
    len++;
    long long x = (long long) v + MAXVAL;
    int c = mp[x]++;
    t.insert(x * ADD + c);
  }

  inline void erase(T v) {
    long long x = (long long) v + MAXVAL;
    int c = mp[x];
    if (c) {
      c--, mp[x]--, len--;
      t.erase(x * ADD + c);
    }
  }

  inline T kth(int k) {
    assert(0 <= k && k <= len - 1);
    return (T) (*t.find_by_order(k) / ADD - MAXVAL);
  }

  inline count(T v) {
    long long x = (long long) v + MAXVAL;
    int c = mp[--x];
    return t.order_of_key(x * ADD + c);
  }

  inline int size() {
    return len;
  }
};
