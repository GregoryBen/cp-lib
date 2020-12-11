template <typename T>
struct suffix_automaton {
  struct node {
    int first_pos = -1;

    int len;
    int link;
    vector<int> inv_link;
    vector<int> next;

    node() {
      next.resize(128, -1);
    }
  };

  int n, sz;
  vector<node> st;

  suffix_automaton(const T &s) : n(s.size()) {
    assert(!s.empty());
    st.resize(2 * n - 1);
    sz = 1;
    int last = 0;
    st[0].link = -1;
    for (int i = 0; i < (int) s.size(); i++) {
      int c = s[i];
      int cur = sz++;
      st[cur].len = i + 1;
      st[cur].first_pos = i;
      int p = last;
      for (; p != -1 && st[p].next[c] == -1; p = st[p].link) {
        st[p].next[c] = cur;
      }
      if (p == -1) {
        st[cur].link = 0;
      } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
          st[cur].link = q;
        } else {
          int clone = sz++;
          st[clone].len = st[p].len + 1;
          st[clone].first_pos = st[q].first_pos;
          st[clone].next = st[q].next;
          st[clone].link = st[q].link;
          for(; p != -1 && st[p].next[c] == q; p = st[p].link) {
            st[p].next[c] = clone;
          }
          st[q].link = clone;
          st[cur].link = clone;
        }
      }
      last = cur;
    }
    for (int i = 1; i < sz; i++) {
      st[st[i].link].inv_link.emplace_back(i);
    }
  }
};
