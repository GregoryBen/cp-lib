// min stack
// all function O(1)
// change to 'max' for max_stack in push function

template <typename T>
struct min_stack {
  struct node {
    T cur;
    T min;
  };

  stack<node> st;

  void push(T x) {
    T y = st.empty() ? x : min(x, st.top().min);
    st.push({x, y});
  }

  void pop() { st.pop(); }
  node top() { return st.top(); }
  int size() { return st.size(); }
  bool empty() { return st.empty(); }
};

// min queue
// all function O(1)

