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

template<typename T> 
struct min_queue {
  deque<T> D, Q;

  void push(T x) {
    while (!D.empty() && x < D.back()) D.pop_back(); // Change to '>' for max_queue
    D.push_back(x);
    Q.push_back(x);
  }

  void pop() {
    if (D.front() == Q.front()) D.pop_front();
    Q.pop_front();
  }

  T top()   { return D.front(); }
  T front() { return Q.front(); }
  T empty() { return Q.empty(); }
  T size()  { return Q.size();  }
};
