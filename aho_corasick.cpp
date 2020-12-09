struct aho_corasick {
  static const int ALPHA = 26;

  struct node {
    int link;
    int escape;
    array<int, ALPHA> next;
  };

  vector<node> tree;

  aho_corasick() {
    tree.emplace_back();
  }

  node& operator[](int i) {
    return tree[i];
  }

  int add(const string &s) {
    assert(!s.empty());
    int v = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (tree[v].next[c] == 0) {
        tree[v].next[c] = tree.size();
        tree.emplace_back();
      }
      v = tree[v].next[c];
    }
    tree[v].escape = v;
    return v;
  }

  void build() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      int u = tree[v].link;
      if (tree[v].escape == 0) {
        tree[v].escape = tree[u].escape;
      }
      for (int c = 0; c < ALPHA; c++) {
        if (tree[v].next[c] != 0) {
          int to = tree[v].next[c];
          tree[to].link = (v == 0 ? 0 : tree[u].next[c]);
          q.push(to);
        } else {
          tree[v].next[c] = tree[u].next[c];
        }
      }
    }
  }
};
