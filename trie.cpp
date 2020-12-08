// max = number of node

template <int MAX>
struct trie {
  int last_node;
  int end[MAX];
  int next[MAX][26];

  int insert(string &s) {
    int cur = 0;
    for (char c : s) {
      int at = (int) c - 'a';
      if (!next[cur][at]) {
        last_node++;
        next[cur][at] = last_node;
      }
      cur = next[cur][at];
    }
    end[cur]++;
    return cur;
  }

  bool search(string s) {
    int cur = 0;
    for (char c : s) {
      int at = (int) c - 'a';
      if (!next[cur][at]) {
        return false;
      }
      cur = next[cur][at];
    }
    return (end[cur] > 0);
  }
};

trie<1000005> tr;
